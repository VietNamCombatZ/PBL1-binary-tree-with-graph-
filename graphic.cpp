#include <iostream>
#include<fstream>
#include <cstdlib>
#include<cstdio>
#include<conio.h>
#include <windows.h>
#include <stack>
#include <queue>
#include <cmath>

#include <graphics.h>

#define E exp(1)
#define Pi M_PI
using namespace std;

struct tNode{
	string data;
	tNode *pLeft, *pRight;
};

tNode *root;

tNode *newNode(string data){
	tNode *node = new tNode();
	node->data = data;
	node->pLeft = NULL;
	node->pRight = NULL;
	return node;
}

// Check  

int heightOfTree(tNode *root){
	if(root==NULL) return 0;
	int height = 1;
	if(root->pLeft==NULL and root->pRight==NULL) return 1;
	return 1 + max(heightOfTree(root->pLeft), heightOfTree(root->pRight));
}


//Read tree follow the order Left node - Middle Node - Right Node
void LNR(tNode *root){
	if(root!=NULL){
		if(root->pLeft != NULL) LNR(root->pLeft);
		if(root!=NULL){
			cout << root->data << " ";
		}
		if(root->pRight != NULL) LNR(root->pRight);
	}
}

void convert_to_char(char* c, string s){
	for(int i=0; i<s.size(); i++){
		c += s[i];
	}
	c[s.size()] = '\0';
}

int size(char *c){
    int i = 0;
    while(c[i] != NULL){
        i++;
    }
    return i;
}

int isdigit(char c){
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

int isoperator(string c){
    if(c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "%" || c == "^") return 1;
    return 0;
}

int isspecial(string s){
    if(s == "ln" || s == "log"  || s == "abs" || s == "cos" || s == "sin" || s == "tan" || s == "cot" || s == "acos" || s == "asin" || s == "atan" || s == "acot" || s == "cosh" || s == "sinh" || s == "tanh" || s == "coth" || s == "sqrt" || s == "cbrt")
        return 1;
    return 0;
}

int pri(string c){
    if(c == "+" || c == "-") return 1;
    if(c == "%") return 2;
    if(c == "*" || c == "/") return 3;
    if(c == "^") return 4;
    if(c == "ln" || c == "log"  || c == "abs" || c == "cos" || c == "sin" || c == "tan" || c == "cot" || c == "acos" || c == "asin" || c == "atan" || c == "acot" || c == "cosh" || c == "sinh" || c == "tanh" || c == "coth" || c == "sqrt" || c == "cbrt") return 5;
    return 0;
}

int pric(char c){
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/' || c == '%') return 2;
    if(c == '^') return 3;
    return 0;
}

int isoperatorc(char c){
    if(c == '*' || c == '/' || c == '^' || c == '+' || c == '-' || c == '%') return 1;
    return 0;
}

double s_to_double(string x){				//string -> double
    if(x == "e") return E;
    if(x == "pi") return Pi;
    
    double tmp = 0;
    string::iterator it = x.begin();
    
    while(*it != '.' && it != x.end()){
        tmp = tmp * 10 + (*it - 48);
        it++;
    }
    if(it == x.end()) return tmp;
    
    double a = 0;
    it = x.end() - 1;
    while(*it != '.'){
        a = (a + (*it - 48.0)) /  10;
        it--;
    }
    tmp += a;
    
    return tmp;
}

void put(char* s, queue<string> &q, stack<string> &st){			// convert expression from string to queue
    for(int i = 0; i < size(s);i++){						// Suffix expression stored in q, operator store in st
        if(s[i] == ' ') continue;
        else if(isdigit(s[i])){								// Read number
            string tmp;
            tmp += s[i];
            while(isdigit(s[i + 1])){
                i++;
                tmp += s[i];
            }
            if(s[i + 1] == '.'){
                tmp += s[++i];
                while(isdigit(s[i + 1])){
                    i++;
                    tmp += s[i];
                }
            }
            q.push(tmp);
        }
        else if(s[i] == '('){								// Read open bracket
            string tmp;
            tmp += s[i];
            st.push(tmp);
        }
        else if(s[i] == ')'){								// Read close bracket
            while(!st.empty() && st.top() != "("){
                q.push(st.top());
                st.pop();
            }
            if(!st.empty()) st.pop();
        }
        // Read special function
        else if(s[i] == 'l' && s[i + 1] == 'n'){
            i++;
            string s = "ln";
            st.push(s);
        }
        else if(s[i] == 'l' && s[i + 1] == 'o' && s[i + 2] == 'g'){
            i+=2;
            string s = "log";
			st.push(s);
        }
        else if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 's'){
            i+=2;
            string s = "abs";
            st.push(s);
        }
        else if(s[i] == 'a' && s[i + 1] == 's' && s[i + 2] == 'i' && s[i+3] == 'n'){
            i += 3;
            string s = "asin";
            st.push(s);
        }
        else if(s[i] == 'a' && s[i + 1] == 'c' && s[i + 2] == 'o' && s[i+3] == 's'){
            i += 3;
            string s = "acos";
            st.push(s);
        }
        else if(s[i] == 'a' && s[i + 1] == 't' && s[i + 2] == 'a' && s[i+3] == 'n'){
            i += 3;
            string s = "atan";
            st.push(s);
        }
        else if(s[i] == 'a' && s[i + 1] == 'c' && s[i + 2] == 'o' && s[i+3] == 't'){
            i += 3;
            string s = "acot";
            st.push(s);
        }
        else if(s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n' && s[i+3] == 'h'){
            i += 3;
            string s = "sinh";
            st.push(s);
        }
        else if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's' && s[i+3] == 'h'){
            i += 3;
            string s = "cosh";
            st.push(s);
        }
        else if(s[i] == 't' && s[i + 1] == 'a' && s[i + 2] == 'n' && s[i+3] == 'h'){
            i += 3;
            string s = "tanh";
            st.push(s);
        }
        else if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 't' && s[i+3] == 'h'){
            i += 3;
            string s = "coth";
            st.push(s);
        }
        else if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's'){
            i+=2;
            string s = "cos";
            st.push(s);
        }
        else if(s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n'){
            i+=2;
            string s = "sin";
            st.push(s);
        }
        else if(s[i] == 't' && s[i + 1] == 'a' && s[i + 2] == 'n'){
            i+=2;
            string s = "tan";
            st.push(s);
        }
        else if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 't'){
            i += 2;
            string s = "cot";
            st.push(s);
        }
        else if(s[i] == 's' && s[i + 1] == 'q' && s[i + 2] == 'r' && s[i+3] == 't'){
            i += 3;
            string s = "sqrt";
            st.push(s);
        }
        else if(s[i] == 'c' && s[i + 1] == 'b' && s[i + 2] == 'r' && s[i+3] == 't'){
            i += 3;
            string s = "cbrt";
            st.push(s);
        }
        else if(s[i] == 'p' && s[i + 1] == 'i'){
            i++;
            string s = "pi";
            st.push(s);
        }
        else if(isoperatorc(s[i])){
            start:
            if(st.empty() || st.top() == "("){
                string tmp;
                
                tmp += s[i];
                st.push(tmp);
                continue;
            }
            else if(pric(s[i]) > pri(st.top())){
                string tmp;
                tmp += s[i];
                st.push(tmp);
            }
            else{
                q.push(st.top());
                st.pop();
                goto start;
            }
        }
        else{
            string tmp;
            tmp += s[i];
            q.push(tmp);
        }
    }
    while(!st.empty()){
        q.push(st.top());
        st.pop();
    }
    
    queue<string> Q = q;
    while(!Q.empty()){
    	cout << Q.front() << " ";
    	Q.pop();
	}
}

tNode* makeExpression(queue<string> q){
	stack<tNode*> stackNode;
	while(!q.empty()){
		if(isoperator(q.front())){
			tNode* P = newNode(q.front());
			
			P->pRight = stackNode.top();
			stackNode.pop();
			
			P->pLeft = stackNode.top();
			stackNode.pop();
			
			stackNode.push(P);
			q.pop();
		}
		else if(isspecial(q.front())){
			tNode* P = newNode(q.front());
			
			P->pRight = stackNode.top();
			stackNode.pop();
			P->pLeft = NULL;
			
			stackNode.push(P);
			q.pop();
		}
		else{
			
			tNode* P = newNode(q.front());
			
			stackNode.push(P);
			q.pop();
		}
	}
	return stackNode.top();
}


// Function to draw a binary tree recursively

int childCount(struct tNode* root){
	int x=0,y=0;
	if(root->pLeft == NULL && root->pRight == NULL)
	{
		return 1;
	}else 	
	{
		
		if(root->pRight !=NULL && root->pLeft==NULL){
			x = 1 + childCount(root->pRight);
		}
		
		if(root->pLeft != NULL){
			x = 1+ childCount(root->pLeft);
		}
		if(root->pRight != NULL){
			y = 1+ childCount(root->pRight);
		}

		if(x >= y){
			return x;
		}
		else{
			return y;
		}
	}
}




/*Code  fixed*/
//check neu la ve node sau thang xuong thi check = 0, con binh thuong check = 1
//check if following node is drawn straight down, check = 0, else check = 1

void drawTree(struct tNode* root, int x, int y, int xOffset, int level, int check) {

    if (root != NULL) {
        // Draw left subtree       
        int xOffset_1 = xOffset*check;        
        if(root -> pRight != NULL && root -> pLeft == NULL){
        	// Draw when node has only 1 child node
//        	delay(1000);
        	line(x,y,x,y+80);

			drawTree(root->pRight, x, y+80, xOffset, level+1, 0); // if xOffset = 0 the following childNode will be place above each other
        	
        	
		}else{		
        if (root->pLeft != NULL) {
        	int cntLeft = childCount(root->pLeft);
        	
        	if (level == 0 ){
//        		delay(1000);
            	line(x, y, x - xOffset*cntLeft, y + 80);
            	drawTree(root->pLeft, x - xOffset*cntLeft, y + 80, xOffset, level + 1, 1 );
			}
			else
			{
//				delay(1000);
				line(x, y, x - xOffset*cntLeft, y + 80);	
            	drawTree(root->pLeft, x - xOffset*cntLeft, y + 80, xOffset, level + 1, 1);
	
			}
		}
        // Draw right subtree
        if (root->pRight != NULL) {
        	int cntRight = childCount(root->pRight);
        	
        	 if (level == 0 ){
//        	 	delay(1000);
            	line(x, y, x + xOffset*cntRight, y + 80);
            	drawTree(root->pRight, x + xOffset*cntRight, y + 80, xOffset , level + 1, 1);
            	
            	

			} else{					
//					delay(1000);
					line(x, y, x + xOffset*(cntRight), y + 80);
				
				    drawTree(root->pRight, x + xOffset*(cntRight), y + 80 , xOffset , level + 1 ,1);
					
				
				

			}

        }
        
    }
    
    
        
        // Draw current node
        setfillstyle(SOLID_FILL, BLUE);
        fillellipse(x, y, 33, 33);
        moveto(x - 10 - 6*(root->data.size() - 1), y - 10);
        char buffer[2]; buffer[1] = '\0';
        for(int i = 0; i < root->data.size(); i++) {
            buffer[0] = root->data[i];
            outtext(buffer);
        }
    }
}



void drawFunction(){
	//	Open graphic mode
	
    int gd = DETECT, gm;
	initwindow(1280,1600);
	
	int startX = 500, startY=50;
	int page =0;

	setlinestyle(CENTER_LINE, 0,3); // change line thickness
	settextstyle(4, HORIZ_DIR, 1); //change character size and font
	setbkcolor(BLUE);
	
//	Create a binary tree
    
    while(1){
    	setactivepage(page);
    	setvisualpage(1-page);
    	setbkcolor(BLACK);
    	cleardevice();
    	setbkcolor(BLUE);
    	drawTree(root, startX, startY, 50, 0, 1);

/*Use arrow key to move the graph, 
  Up_key to see upper part
  Down_key to see lower part
  Right_key to see right_part
  Left_key to see left_part
  SPACE to quit the graphic window and go back to the menu window*/
    	
    	if(GetAsyncKeyState(VK_RIGHT)){
    		startX -= 20; //Move the graph to the right
		}else if(GetAsyncKeyState(VK_LEFT)){
			startX += 20;  //Move the graph to the left
		}else if( GetAsyncKeyState(VK_UP) ){
			
			startY +=20;   //Move the graph up
		}else if( GetAsyncKeyState(VK_DOWN)){
			startY -= 20;  //Move the graph down
		}else if(GetAsyncKeyState(VK_SPACE)){
			break;
		}
		delay(10);
		page = 1 - page;
    	
	}
	

  // Close graphics mode
    getch();
    
    
    closegraph();
}


void readDataFromFile(FILE *fptr)
{
	queue<string> q;
	stack<string> st;
	char expression[100];
	   
	fgets(expression, 100, fptr);
    cout << expression << endl;
    put (expression, q, st);
        
    root = makeExpression(q);
	
	cout << "\nLNR: \n";
	LNR(root);
	
	drawFunction();
	return;
}

void enterExpression(){
	queue<string> q;
	stack<string> st;
	char c[1000];
	char expression[100];

	cout << "Enter Expression : ";
	getchar();
	gets(c); 

	cout << c << endl;
	put(c, q, st);

	root = makeExpression(q);	
	cout << "\nLNR: \n";
	LNR(root);

	drawFunction();
	
}


int main(){
	queue<string> q;
	stack<string> st;
    FILE *fptr;
    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
	char c[1000];
	char expression[100];
	int menu;
	
	
	int option = -1;
	int check;
	
//	colors(BLUE);
	SetConsoleTextAttribute(h, 6);
		
	while(1){
		printf("\n\n-----Select the code file-----\n\n");
		printf("File-1: 3*atan(ln(7.54-8/344)*asin(64*log(7)))-7*6+cos(8-(9^67))\n");
		printf("File-2: cos(3*ln(pi)-9.6/77)-7*8+ln(6*4-32)\n");
		printf("File-3: atan(88)-9/sinh(34)+6*sqrt(7.78-cosh(78)) \n");
		printf("File-4: log(7.66-abs(ln(93)-6*7))+69.5/(3*6-sinh(83))\n");
		printf("\n9. Enter your own expression:\n");
		printf("0. Quit the program\n");
		printf("\n--------------------------------\n");
		printf("Enter your choice:");
		scanf("%d", &option);
		
		
		check = 0;
		switch (option){
			case 0:{
				check =1;
				break;
			}
			case 1: {
				fptr = NULL;
				fptr = fopen("Input_expression_01.txt", "r");
				readDataFromFile(fptr);	
							
				break;
			}
			case 2: {
				fptr = NULL;
				fptr = fopen("Input_expression_02.txt", "r");
				readDataFromFile(fptr);	
				
				break;
			}
			case 3: {
				fptr = NULL;
				fptr = fopen("Input_expression_03.txt", "r");
				readDataFromFile(fptr);	
					
				break;
			}
			case 4: {
				fptr = NULL;
				fptr = fopen("Input_expression_04.txt", "r");
				readDataFromFile(fptr);	
					
				break;
			}
			case 9:{
				enterExpression();			
				break;
			}
			default: {
				printf("Invalid option\n");	
				break;
			}
		}
		if( check == 1){
			break;
		}
	}
	return 0;
}

//cos(9.35*7-atan(6+ln(3^7)))*7-9/(7-533*7/(9-16*3))/(atan(7-ln(6^77))/9-acos(8*3.44)) 
// cos(7-9*6^7-6*atan(7-87))
