#include<bits/stdc++.h>
using namespace std;
#include "parser.hpp"

#define N 10000
#define no_NT 33
#define no_T 36

stack<string> main_stack;
int top;
int rule_number;
int curr_trow=0;
int GLOBALCOUNT=0;
// std::ofstream out("output.txt");
vector<string> productions={
"",
"S -> { GLOBAL } FUNCTIONS { STATEMENTS }",
"GLOBAL -> DECLARATIONS",
"FUNCTIONS -> FUNCTION FUNCTIONS",
"FUNCTIONS -> ''",
"FUNCTION -> DATATYPE main ( PARAMETERS ) { STATEMENTS RETURN }",
"FUNCTION -> void main ( PARAMETERS ) { STATEMENTS }",
"DECLARATIONS -> DEFINITION DECLARATIONS",
"DECLARATIONS -> ASSIGNMENT DECLARATIONS",
"DECLARATIONS -> ''",
"DEFINITION -> DATATYPE id ;",
"ASSIGNMENT -> id = SEQ ;",
"PARAMETERS -> DEFINITION C PARAMETERS",
"PARAMETERS -> ''",
"C -> ,",
"C -> ''",
"DATATYPE -> int",
"DATATYPE -> float",
"DATATYPE -> char",
"DATATYPE -> string",
"RETURN -> return SEQ ;",
"STATEMENTS -> STATEMENT STATEMENTS",
"STATEMENTS -> ''",
"STATEMENT -> COND",
"STATEMENT -> LOOP",
"STATEMENT -> IO",
"STATEMENT -> DECLARATIONS",
"SEQ -> ARITH TEMP",
"TEMP -> ''",
"TEMP -> OPERATOR ARITH",
"ARITH -> F ARITH2",
"ARITH2 -> OP F ARITH2",
"ARITH2 -> ''",
"F -> id",
"F -> CONSTANT",
"OP -> +",
"OP -> -",
"OP -> /",
"OP -> *",
"CONSTANT -> integer",
"CONSTANT -> floatnum",
"CONSTANT -> strn",
"CONSTANT -> character",
"IO -> input IN_2 ;",
"IO -> output OUT_2 ;",
"IN_2 -> >> SEQ IN_2",
"IN_2 -> ''",
"OUT_2 -> << SEQ OUT_2",
"OUT_2 -> ''",
"COND -> if ( RELATIONAL ) { STATEMENTS } else { STATEMENTS }",
"LOOP -> for ( id ; RELATIONAL ; id = ARITH ) { STATEMENTS }",
"LOOP -> while ( RELATIONAL ) { STATEMENTS }",
"RELATIONAL -> ARITH OPERATOR ARITH",
"OPERATOR -> <=",
"OPERATOR -> >=",
"OPERATOR -> <",
"OPERATOR -> >",
"OPERATOR -> ==",
"",
"",
"snkasdn"
};

vector<string> non_terminals = {
	"","S","GLOBAL","FUNCTIONS","FUNCTION","DECLARATIONS","DEFINITION","ASSIGNMENT","PARAMETERS","C","DATATYPE","RETURN","STATEMENTS","STATEMENT","SEQ","TEMP","ARITH","ARITH2","F","OP","CONSTANT","IO","IN_2","OUT_2","COND","LOOP","RELATIONAL","OPERATOR"

};

vector<string> terminals = {
	"","{","}","main","(",")","void","id",";","=",",","int","float","char","string","return","+","-","/","*","integer","floatnum","strn","character","input","output",">>","<<","if","else","for","while","<=",">=","<",">","==","$"

};


vector<vector<int>> transition_table={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59},{0,0,58,0,0,0,0,2,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,58,0,0,0,0,3,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,59,0,0,0,0,6,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,58,0,0,0,0,8,0,0,0,7,7,7,7,58,0,0,0,0,0,0,0,0,58,58,0,0,58,0,58,58,0,0,0,0,0,0},{0,0,59,0,0,59,0,59,0,0,59,10,10,10,10,59,0,0,0,0,0,0,0,0,59,59,0,0,59,0,59,59,0,0,0,0,0,0},{0,0,59,0,0,0,0,11,0,0,0,59,59,59,59,59,0,0,0,0,0,0,0,0,59,59,0,0,59,0,59,59,0,0,0,0,0,0},{0,0,0,0,0,58,0,0,0,0,0,12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,58,0,0,0,0,14,58,58,58,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,59,0,0,0,59,0,0,0,16,17,18,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,59,0,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,58,0,0,0,0,21,0,0,0,21,21,21,21,58,0,0,0,0,0,0,0,0,21,21,0,0,21,0,21,21,0,0,0,0,0,0},{0,0,58,0,0,0,0,26,0,0,0,26,26,26,26,58,0,0,0,0,0,0,0,0,25,25,0,0,23,0,24,24,0,0,0,0,0,0},{0,0,0,0,0,0,0,27,59,0,0,0,0,0,0,0,0,0,0,0,27,27,27,27,0,0,59,59,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,58,58,0,0,0,0,29,29,29,29,29,0},{0,0,0,0,0,59,0,30,59,0,0,0,0,0,0,0,0,0,0,0,30,30,30,30,0,0,59,59,0,0,0,0,59,59,59,59,59,0},{0,0,0,0,0,58,0,0,58,0,0,0,0,0,0,0,31,31,31,31,0,0,0,0,0,0,58,58,0,0,0,0,58,58,58,58,58,0},{0,0,0,0,0,59,0,33,59,0,0,0,0,0,0,0,59,59,59,59,34,34,34,34,0,0,59,59,0,0,0,0,59,59,59,59,59,0},{0,0,0,0,0,0,0,59,0,0,0,0,0,0,0,0,35,36,37,38,59,59,59,59,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,59,0,0,59,0,0,0,0,0,0,0,59,59,59,59,39,40,41,42,0,0,59,59,0,0,0,0,59,59,59,59,59,0},{0,0,59,0,0,0,0,59,0,0,0,59,59,59,59,59,0,0,0,0,0,0,0,0,43,44,0,0,59,0,59,59,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,0,0,0,0,0,0,0,0,0,0},{0,0,59,0,0,0,0,59,0,0,0,59,59,59,59,59,0,0,0,0,0,0,0,0,59,59,0,0,49,0,59,59,0,0,0,0,0,0},{0,0,59,0,0,0,0,59,0,0,0,59,59,59,59,59,0,0,0,0,0,0,0,0,59,59,0,0,59,0,50,51,0,0,0,0,0,0},{0,0,0,0,0,59,0,52,59,0,0,0,0,0,0,0,0,0,0,0,52,52,52,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,59,0,0,0,0,0,0,0,0,0,0,0,0,59,59,59,59,0,0,0,0,0,0,0,0,53,54,55,56,57,0}
};

int check_nt(string a){
	
	for(int i=0;i<non_terminals.size();i++){
		if(non_terminals[i]== a){
			return 1;
		}
	}
	return 0;
}

int find_terminal(string a){
	int i=0;
	while(i<terminals.size()){
		if(terminals[i++]== a)
			return --i;
	}
	return 0;
}

int find_non_terminal(string a){
	int i=0;
	while(i<non_terminals.size()){
		if(non_terminals[i++]== a)
			return --i;
	}
	return 0;
}

vector<string> tokenizer(string a)
{
	vector<string> ans;
	string s;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]==' ')
		{
			ans.push_back(s);
			s.clear();
		}
		else if(a[i]=='\n')
		{
			ans.push_back(s);
			s.clear();
		}
		else if(a[i]=='\t')
		{
			ans.push_back(s);
			s.clear();			
		}
		else
		{
			s.push_back(a[i]);
		}
	}
	ans.push_back(s);
	return ans;
}


int shift_move(int production_number)
{
	// out<<"hello"<<endl;
	cout<<production_number<<endl;
	if(production_number==0){
		cout<<"SKIP ERROR!"<<endl<<endl;
		curr_trow++;
		return -1;
	}
	if(!main_stack.empty())
		main_stack.pop();
	else
	{
		cout<<"STACK UNDERFLOW"<<endl<<endl;
		return -2;
	}
	int flagesh;
	if(production_number==58){
		cout<<endl<<"NULL TRANSITION"<<endl<<endl;
//		main_stack.pop();
		//return -1;
	}
	if(production_number==59)	
	{
		cout<<endl<<"SYNC ERROR"<<endl<<endl;
//		main_stack.pop();
		//return -1;
	}
	
	string production;
	production=productions[production_number];
	vector<string> temp;
	temp = tokenizer(production);
	for(int i=temp.size()-1;i>=0;i--)
	{
		if(temp[i]!="->")
		{
			main_stack.push(temp[i]);
		}
		else
		{
			break;
		}
	}
	if((production_number==58 or production_number==59) )
	{
		// out<<"asdasda"<<endl;
		if(!main_stack.empty())
			main_stack.pop();
		else
			{
				cout<<"STACK UNDERFLOW!!"<<endl;
				return -2;
			}
	}

	return 0;

}

int print_contents(){
	int i;
	cout<<"INPUTS:"<<endl;
	for(i=curr_trow;i<tRow;i++)
		cout<<tokens[i]<<" ";
		// printf("%s ", tokens[i]);

	cout<<endl<<endl;
	stack<string> temp_stack1;
	temp_stack1 = main_stack;
	cout<<"STACK:"<<endl;
	for(i=main_stack.size()-1;i>=0;i--)
	{	// printf("%s ", main_stack.top());
		cout<<temp_stack1.top()<<" ";
		temp_stack1.pop();
	}
	cout<<endl<<endl;

	return 0;
}

int main(){
	string filename;
	cout<<"ENTER INPUT FILENAME: ";
	std::cin>>filename;
	cout<<"YOU WILL FIND YOUR OUTPUT IN output.txt"<<endl;
	driver(filename);
	cout<<"hi"<<endl;
	main_stack.push("$");
	main_stack.push("S");
	tokens.push_back("$");
	tRow++;

	cout<<"hello"<<endl;
	while(curr_trow<tRow ){
		cout<<"Current token: "<< tokens[curr_trow]<< endl;
		print_contents();

		string stack_top;
		if(!main_stack.empty())
			stack_top=main_stack.top();
		else
		{
			cout<<"STACK UNDERFLOW!!"<<endl;
			return 0;
		}
		int is_nt= check_nt(stack_top);

		if(is_nt){
			int ter_no= find_terminal(tokens[curr_trow]);

			int non_ter_no=find_non_terminal(stack_top);
			cout<<"NT: "<<non_ter_no<<" T: "<<ter_no<<endl;
			rule_number= transition_table[non_ter_no][ter_no];
			cout<<"RULE NO:"<<rule_number<<endl;
			// out<<rule_number<<endl;
			cout<< "Production: "<<productions[rule_number]<<endl;
			// out<<rule_number<<endl;
			// shift_move(rule_number);
			if(shift_move(rule_number)==-2)
			{
				return 0;
			}
		}

		else{
			if(tokens[curr_trow]==stack_top)
			{
				cout<< endl<< "MATCH!"<<endl<<endl;
				cout<<"----------------------------------------------------------------------------------------------------------------"<<endl<<endl;
				if(!main_stack.empty())
					main_stack.pop();

				else
				{
					cout<<"STACK UNDERFLOW"<<endl;
					return 0;
				}
			}

			else
			{
				cout<<endl<<"MISMATCHED TERMINALS!!....Finishing Program."<<endl<<endl;
				// if(main_stack.size()>0)
				// 	// main_stack.pop();
				// else
				// {
				// 	// out<<"STACK UNDERFLOW"<<endl;
				// 	// return 0;
				// }
				return 0;
			}
			curr_trow++;
		}
	}
	// out<<productions[57]<<endl<<productions[59]<<endl<<productions[60]<<endl;
	return 0;
}
