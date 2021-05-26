// Group Number 37
//Language Name:  Viper
//2017B4A70885H   Suhas Reddy N
//2017B3A71048H   Shanmukh Kali Prasad

#include<bits/stdc++.h>
using namespace std;

#define num_key 20
#define num_ops 18
#define num_delim 8

#define Range_key 1
#define Range_op 50
#define Range_delim 100

vector<string> keyWords= {"int","float","break","long","char","for","if","switch","else","while","goto","continue","return","auto","double","boolean","string","default","do","case"};

vector<string> operators = { "+", "-", "*", "/", "%", "!", "?", ":", ">", "<", ":=", "==", ">=", "<=", "!=", "&&", "||", "="};
vector<string> delimiters = { "{", "}", "(", ")", "[", "]", ";", ","};

string buffer;

int token_no = 1;
int line_no = 0;
int flag = 0;

// Function to check for operator(return 1) or delimiter(return 2) for tokenization
int op_delim(char a)
{   
    int i;
    for(i=0;i<num_ops;i++)
    {
        if(a == operators[i][0])
            return 1;
    }
    for(i=0;i<num_delim;i++)
    {	
        if(a == delimiters[i][0])
        {
        	// cout<<"tru";
        	return 2;
        }   
    }
    return 0;
}

void breakingFloat(string Tok)
{
    bool point=false;
    int i;
    string s;
    for(i=0;i<Tok.length();i++)
    {
        if(Tok[i]!='.')
        {
            s.push_back(Tok[i]);
        }
        else if(Tok[i]=='.' && !point)
        {
            point  = true;
            s.push_back('.');
        }
        else if(Tok[i]=='.' && point)
        {
            break;
        }
    }
    cout<<"Token "<<153<<", float "<<s<<", line num: "<<line_no<<endl;
    Tok.erase(0,i);
    cout<<"Token "<<404<<", invalid "<<Tok<<", line num: "<<line_no<<endl;

}

int regexp(string tok)
{
	int i;

    //invalid token
    if(tok.length() == 0)
        return 0;
    if(tok[0]=='"' && tok[tok.length()-1]=='"')
    {
        cout<<"Token "<<154<<", string "<<tok<<", line num: "<<line_no<<endl;
        return 0;
    }

    //matching with keywords
    for(i=0;i<num_key;i++)
    {
        if(tok==keyWords[i])
        {
        	cout<<"Token "<<Range_key+i<<", keyword "<<tok<<", line num: "<<line_no<<endl;
            return 0;
        }
    } 

    //matching with operators
    for(i=0;i<num_ops;i++)
    {
        if(tok==operators[i])
        {
        	cout<<"Token "<<Range_op+i<<", operator "<<tok<<", line num: "<<line_no<<endl;
            return 0;
        }
    }

    //matching with delimiter
    for(i=0;i<num_delim;i++)
    {
        if(tok==delimiters[i])
        {
        	cout<<"Token "<<Range_delim+i<<", delimiter "<<tok<<", line num: "<<line_no<<endl;
            return 0;
        }
    }

    //DFA for others
    int state = 1;
    i = 0;
    char t;
    while(tok[i] != '\0' && state != 10)
    {
        t = tok[i++];
        switch(state)
        {
            case 1:
                if(isalpha(t))
                    state = 2;
                else if(t == '+' || t == '-')
                    state = 3;
                else if(isdigit(t))
                    state = 4;
                else if(t == '"')
                    state = 6;
                else
                    state = 10;
                break;
            case 2:
                if(isalpha(t) || isdigit(t) || t == '_')
                    state = 2;
                else
                    state = 10;
                break;
            case 3:
                if(isdigit(t))
                    state = 4;
                else if(t == '0')
                    state = 11;
                else
                    state = 10;
                break;
            case 4:
                if(isdigit(t))
                    state = 4;
                else if(t == '.')
                    state = 7;
                else 
                    state = 10;
                break;
            case 5:
                if(t == '.')
                    state = 7;
                else
                    state = 10;
                break;
            case 6:
                if(t != '"')
                    state = 6;
                else
                    state = 9;
                break;
            case 7:
                if(isdigit(t))
                    state = 8;
                else 
                    state = 10;
                break;
            case 8:
                if(isdigit(t))
                    state = 8;
                else if(t=='.')
                    state = 12;
                else
                    state = 10;
                break;
            case 9:
                state = 10;
                break;
            case 10:
                cout<<"invalid token\n";
                return 10;
            case 11:
                if(t == '.')
                    state = 7;
                else
                    state = 10;
            case 12:
                state = 12;
        }
    }

    char type[10];
    
    switch(state)
    {
        case 2:
        		// Identifier
        	cout<<"Token "<<150<<", id "<<tok<<", line num: "<<line_no<<endl;
            break;
        case 4:
        		//Integers from 0-9
        	cout<<"Token "<<151<<", integer "<<tok<<", line num: "<<line_no<<endl;
            // printf("Token %d, integer %s, line number %d\n",151,tok,line_no);
            break;
        case 8:
        	// Float
        	cout<<"Token "<<153<<", float "<<tok<<", line num: "<<line_no<<endl;
            break;
        case 9:
        	//empty string
        	cout<<"Token "<<154<<", string "<<tok<<", line num: "<<line_no<<endl;
            break;
        case 12:
            breakingFloat(tok);
            break;
        default:
        	cout<<"Token "<<404<<", invalid "<<tok<<", line num: "<<line_no<<endl;
            break;
    }
    return state;
}


int tokenizeBuffer(string tok)
{
	int i=0,curr,flag1 = 0;
	// cout<<"hello";
	//initialise buffer?
	string buffer;
	while(i<tok.length())
    {   
		//Check for operator and delimiter
        curr = op_delim(tok[i]);
        
        // Operator has been read
        if(flag1 == 1)
        {
			//Boolean op.
            if(tok[i] == '=' || tok[i] == '&' || tok[i] == '|')
            {
                buffer+=tok[i];
                flag1 = 2;
            }
            regexp(buffer);
            buffer="";
            if(flag1 != 2)
            {
                buffer+= tok[i];
                if(op_delim(tok[i]))
                {
                    regexp(buffer);
                    buffer="";
                }
            }
            flag1 = 0;
            i++;
            continue;
        }
        // Neither of Op or Delimiter
        if(curr == 0)
            buffer+= tok[i];
		
		// tok[i] is an operator
        else if(curr == 1)
        {
            flag1 = 1;
            // cout<<buffer<<endl;
            regexp(buffer);
            // cout<<"buffered"<<endl;
            buffer="";
            // cout<<buffer<<endl;
            buffer+= tok[i];
            // cout<<buffer<<endl;
        }
		// tok[i] is delimiter
        else if(curr == 2)
        {
            // cout<<buffer<<endl;
            regexp(buffer);
            // cout<<"buffered"<<endl;
            buffer="";
            buffer+= tok[i];
            regexp(buffer);
            buffer="";
        }
        i++;
    }
    //tok ends but buffer still isnt empty like identifiers
    if(buffer.length()) 
    {
        regexp(buffer);
    }
    return 0;
}

int scanLine(string line)
{
	if(line.length()>=2 && line[0]=='/' && line[1]=='/')   return 0;

    for(int i=0;i<line.length();i++)
    {
        // cout<<line[i];
        if(flag==0 && line[i]=='/' && i+1<line.length() && line[i+1]=='/')
        {
            flag=1;
            i++;
        }
        else if(flag==1 && line[i]=='\n')
            flag=0;
        else if(flag==0 && line[i]=='/' && i+1<line.length() && line[i+1]=='*')
        {
            flag=2;
            i++;
        }
        else if(flag==2 && line[i]=='*' && i+1<line.length() && line[i+1]=='/')
        {
            flag=0;
            i++;
        }
        else if(flag==0 && line[i]=='"')
        {
            if(buffer.length())
                tokenizeBuffer(buffer);
            buffer="";
            flag=3;
            buffer+=line[i];
        }
        else if(flag==3 && line[i]!='"')
        {
            buffer+=line[i];
            // cout<<buffer<<endl;
        }
        else if(flag==3 && line[i]=='"')
        {
            flag=0;
            buffer+=line[i];
            regexp(buffer);
            buffer="";
        }
        else if(flag==0)
        {
            while(line[i]=='\t')
                i++;
            if(line[i]==' ' || line[i]=='\n' || line[i]=='\0' || line[i]=='\r')
            {
                if(line.length())
                    tokenizeBuffer(buffer);
                buffer="";
            }
            else
            {
                buffer+=line[i];
            }
        }

	}
	return 0;
}

int main()
{
	fstream newfile;
	string s;
	cin>>s;
	newfile.open(s, ios::in);
	string line;
	while(getline(newfile,line))
	{
	    line_no++;
	    // cout<<"debug: "<<line<<endl;
        if(!line.length())  continue;
        line+='\n';
	    scanLine(line);
	    // cout<<endl;
	}
	newfile.close();
}
