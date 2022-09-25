static bool flag = true;

CPU& CPU::do_assembly(std::ifstream & fin)
{
    std::string token {};
    while(!fin.eof())
    {
        fin >> token;
        int which_keyword = checking_keyword(token);
        switch(which_keyword)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                std::cout << "Logic error in " << line << "'th line !" << std::endl;
                exit(1);
                break;
            case 10:
                do_move(fin);
                break;
            case 11:
                do_add(fin);
                break;
            case 12:
                do_sub(fin);
                break;
            case 13:
                do_mul(fin);
                break;
            case 14:
                do_div(fin);
                break;
            case 15:
                do_jmp(fin);
                break;
            case 16:
                do_jl(fin);
                break;
            case 17:
                do_jg(fin);
                break;
            case 18:
                do_je(fin);
                break;
            case 19:
                do_cmp(fin);
                break;
            case -1:
                if(is_label(token))
                {
                    keywords.push_back(token);
                    flag = true;
                    std::string end;
                    char whitespace = ' ';
                    std::ofstream cycle;
                    fin >> end;
                    cycle.open("file_for_jmp.txt");
                    while((end!= "jmp") && (end != "jl") && (end != "jg") && (end != "je"))
                    {
                        cycle << end;
                        cycle << whitespace;
                        fin >> end;
                        if(checking_keyword(end) - 10 >= 0)
                        {
                            cycle << "\n";
                            line++;
                        }
                    }
                    cycle.close();
                    if(end == "jmp")
                    {
                        do_jmp(fin);
                    }
                    else if(end == "jl")
                    {
                        do_jl(fin);
                    }
                    else if(end == "jg")
                    {
                        do_jg(fin);
                    }
                    else if(end == "je")
                    {
                        do_je(fin);
                    }
                }
                else
                {
                    std::cout << "Lexical error in " << line << "'th line !" << std::endl;
                }
                
                break;
        }
        ++line;
    }
    return *this;
}

void CPU::do_je(std::ifstream& fin)
{
    std::string check;
    fin >> check;
    check.push_back(':');
    if(checking_keyword(check) > 19)
    {
        first_time:
        std::ifstream cycin;
        cycin.open("file_for_jmp.txt");
        std::string str;
        while(str != "cmp")
        {
            cycin >> str;
        }
        if(do_cmp(cycin) == 0)
        {
            flag = true;
            cycin.close();
            cycin.clear();
            std::ifstream cycle;
            cycle.open("file_for_jmp.txt");
            std::string str;
            do_assembly(cycle);
            cycle.close();
            cycle.clear();
            if(flag)
            {
                goto first_time;
            }
            
        }
        else{flag = false;}
    }
    else
    {
        std::cout << "The label name is wrong after [je]" << std::endl;
        exit(1);
    }
}

void CPU::do_jg(std::ifstream& fin)
{
    std::string check;
    fin >> check;
    check.push_back(':');
    if(checking_keyword(check) > 19)
    {
        first_time:
        std::ifstream cycin;
        cycin.open("file_for_jmp.txt");
        std::string str;
        while(str != "cmp")
        {
            cycin >> str;
        }
        if(do_cmp(cycin) == 1)
        {
            flag = true;
            cycin.close();
            cycin.clear();
            std::ifstream cycle;
            cycle.open("file_for_jmp.txt");
            std::string str;
            do_assembly(cycle);
            cycle.close();
            cycle.clear();
            if(flag)
            {
                goto first_time;
            }
            
        }
        else{flag = false;}
    }
    else
    {
        std::cout << "The label name is wrong after [jg]" << std::endl;
        exit(1);
    }
}

void CPU::do_jl(std::ifstream& fin)
{
    std::string check;
    fin >> check;
    check.push_back(':');
    if(checking_keyword(check) > 19)
    {
        first_time:
        std::ifstream cycin;
        cycin.open("file_for_jmp.txt");
        std::string str;
        while(str != "cmp")
        {
            cycin >> str;
        }
        if(do_cmp(cycin) == 2)
        {
            flag = true;
            cycin.close();
            cycin.clear();
            std::ifstream cycle;
            cycle.open("file_for_jmp.txt");
            std::string str;
            do_assembly(cycle);
            cycle.close();
            cycle.clear();
            if(flag)
            {
                goto first_time;
            }
            
        }
        else{flag = false;}
    }
    else
    {
        std::cout << "The label name is wrong after [jl]" << std::endl;
        exit(1);
    }
}

int CPU::do_cmp(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if((checking_keyword(str) < 0) && (checking_keyword(str) > 9))
    {
        std::cout << "In the line of " << line << " you have syntax error after cmp" << std::endl;
        exit(1);
    }
    else
    {
        std::string new_str;
        fin >> new_str;
        if((checking_keyword(new_str) >= 0) && (checking_keyword(new_str) <= 9))
        {
            if(mmap[str] == mmap[new_str])
            {
                return 0;
            }
            else if(mmap[str] > mmap[new_str])
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
        else if(is_digit(new_str[0]))
        {
            int num = 0;
            for(int i = 0; i < new_str.size(); i++)
            {
                num = num + pow(10,(new_str.size() - 1 - i))*(new_str[i] - 48);
            }
            if(mmap[str] == num)
            {
                return 0;
            }
            else if(mmap[str] > num)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }
    return -1;
}


void CPU::do_jmp(std::ifstream& fin)
{
    std::string check;
    fin >> check;
    check.push_back(':');
    if(checking_keyword(check) > 19)
    {
    first_time:
        std::ifstream cycin;
        cycin.open("file_for_jmp.txt");
        do_assembly(cycin);
        cycin.close();
        cycin.clear();
        if(flag)
        {
            flag = false;
            goto first_time;
        }
    }
    else
    {
        std::cout << "The label name is wrong" << std::endl;
        exit(1);
    }
}

void CPU::do_move(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if(checking_keyword(str) < 0 || checking_keyword(str) > 9)
    {
        std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
        return;
    }
    else
    {
        std::string tmp = "";
        fin >> tmp;
        if(checking_keyword(tmp) >= 0 && checking_keyword(tmp) <= 9)
        {
            mmap.erase(str);
            mmap.insert(make_pair(str,mmap[tmp]));
            return;
        }
        int num = 0;
        for(int i = 0; i < tmp.size(); i++)
        {
            num = num + pow(10,(tmp.size() - 1 - i))*(tmp[i] - 48);
        }
        mmap.erase(str);
        mmap.insert(make_pair(str,num));
    }
}

void CPU::printing()
{
    std::map <std::string, int> :: iterator it;
    std::cout << "\nRegisters below\n\n";

    for(it = mmap.begin(); it != mmap.end(); ++it)
    {
        std::cout << "\t" << (it -> first) << " - " << it -> second <<  std::endl;
    }
    std::cout << std::endl;
}

void CPU::do_add(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if(checking_keyword(str) < 0 && checking_keyword(str) > 9)
    {
        std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
        return;
    }
    else
    {
        std::string tmp{};
        fin >> tmp;
        if(is_digit(tmp[0]))
        {
            int num = 0;
            for(int i = 0; i < tmp.size(); i++)
            {
                num = num + pow(10,(tmp.size() - 1 - i))*(tmp[i] - 48);
            }
            mmap[str] += num;
        }
        else if(checking_keyword(str) >= 0 && checking_keyword(str) <= 9)
        {
            mmap[str] += mmap[tmp];
        }
        else
        {
            std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
            return;
        }
    }
}

void CPU::do_sub(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if(checking_keyword(str) < 0 && checking_keyword(str) > 9)
    {
        std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
        return;
    }
    else
    {
        std::string tmp{};
        fin >> tmp;
        if(is_digit(tmp[0]))
        {
            int num = 0;
            for(int i = 0; i < tmp.size(); i++)
            {
                num = num + pow(10,(tmp.size() - 1 - i))*(tmp[i] - 48);
            }
            mmap[str] -= num;
        }
        else if(checking_keyword(str) >= 0 && checking_keyword(str) <= 9)
        {
            mmap[str] -= mmap[tmp];
        }
        else
        {
            std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
            return;
        }
    }
}

void CPU::do_mul(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if(checking_keyword(str) < 0 && checking_keyword(str) > 9)
    {
        std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
        return;
    }
    else
    {
        std::string tmp{};
        fin >> tmp;
        if(is_digit(tmp[0]))
        {
            int num = 0;
            for(int i = 0; i < tmp.size(); i++)
            {
                num = num + pow(10,(tmp.size() - 1 - i))*(tmp[i] - 48);
            }
            mmap[str] *= num;
        }
        else if(checking_keyword(str) >= 0 && checking_keyword(str) <= 9)
        {
            mmap[str] *= mmap[tmp];
        }
        else
        {
            std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
            return;
        }
    }
}

void CPU::do_div(std::ifstream& fin)
{
    std::string str;
    fin >> str;
    if(checking_keyword(str) < 0 && checking_keyword(str) > 9)
    {
        std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
        return;
    }
    else
    {
        std::string tmp{};
        fin >> tmp;
        if(is_digit(tmp[0]))
        {
            int num = 0;
            for(int i = 0; i < tmp.size(); i++)
            {
                num = num + pow(10,(tmp.size() - 1 - i))*(tmp[i] - 48);
            }
            mmap[str] /= num;
        }
        else if(checking_keyword(str) >= 0 && checking_keyword(str) <= 9)
        {
            mmap[str] /= mmap[tmp];
        }
        else
        {
            std::cout << "Here may be syntax error or /n in " << line << "'th line !" << std::endl;
            return;
        }
    }
}

bool CPU::is_label(std::string& str)
{
    if(str[str.size() - 1] == ':')
    {
        return true;
    }
    return false;
}

bool CPU::is_digit(const char& ch)
{
    bool check = (ch <= 57 && ch >= 48);
    return check;
}

int CPU::checking_keyword (std::string& first_token)
{
    for (int i = 0; i < keywords.size(); i++)
    {
        if(keywords[i] == first_token)
        {
            return i;
        }
    }
    return -1;
}
