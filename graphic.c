#include <bits/stdc++.h>
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
int xOffpos = 50;
int lCnt = 0;
int rCnt = 0;


int childCount(struct tNode* root){
	int x,y;
	if(root->pLeft == NULL && root->pRight == NULL)
	{
		return 1;
	}else{
		if(root->pLeft != NULL){
			x = 1+ childCount(root->pLeft);
		}
		if(root->pRight != NULL){
			y = 1+ childCount(root->pRight);

		}


		if(x>=y){
			return x;
		}
		else{
			return y;
		}
	}
}




/*Code  fixed*/
//check neu la ve node sau thang xuong thi check = 0, con binh thuong check = 1
//check iff following node is drawn straight down, check = 0, else check = 1

void drawTree(struct tNode* root, int x, int y, int xOffset, int level, int check) {
    if (root != NULL) {
        // Draw left subtree
        
        int xOffset_1 = xOffset*check;
        
        if(root -> pRight != NULL && root -> pLeft == NULL){
        	// Draw when node has only 1 child node
        	line(x,y,x,y+80);

			drawTree(root->pRight, x, y+80, xOffset, level+1, 0); // if xOffset = 0 the following childNode will be place above each other
        	
        	
		}else{
		
		
        if (root->pLeft != NULL) {
        	int cntLeft = childCount(root->pLeft);
        	
        	if (level == 0 ){
            	line(x, y, x - xOffset, y + 80);
            	drawTree(root->pLeft, x - xOffset, y + 80, xOffset/3, level + 1, 1 );

			}
			else
			{

				
				line(x, y, x - xOffset, y + 80);
            	drawTree(root->pLeft, x - xOffset, y + 80, xOffset, level + 1, 1);

				
			}
		}
        	

        
        
        // Draw right subtree
        if (root->pRight != NULL) {
        	int cntRight = childCount(root->pRight);
        	
        	 if (level == 0 ){
            	line(x, y, x + xOffset, y + 80);
            	drawTree(root->pRight, x + xOffset, y + 80, xOffset / 3, level + 1, 1);
            	
            	

			} else{
				
				if(cntRight < 2){
					line(x, y, x + xOffset*(cntRight), y + 80);
				drawTree(root->pRight, x + xOffset*(cntRight), y + 80 , xOffset , level + 1, 1 );
				}else{
					line(x, y, x + xOffset*(cntRight-1), y + 80);
				drawTree(root->pRight, x + xOffset*(cntRight-1), y + 80 , xOffset , level + 1 ,1);
					
				}
				

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



int main(){
	queue<string> q;
	stack<string> st;
	char c[1000];
	char expression[100];
	
	int option = -1;
	
	cout << "Enter Expression : ";
	
	
//	FILE *fptr;
//	
//	
//	
//	
////	fptr = fopen("Input_expression_01.txt", "r");
////	fptr = fopen("Input_expression_02.txt", "r");
////	fptr = fopen("Input_expression_03.txt", "r");
//
//    
//
//    fgets(expression, 100, fptr);
//cout << expression << endl;
//    put (expression, q, st);
	
	gets(c); cout << c << endl;
	
	put(c, q, st);

    
    
	
	root = makeExpression(q);
	
	cout << "\nLNR: \n";
	LNR(root);
	
//	Open graphic mode
	
    int gd = DETECT, gm;
	initwindow(1000,1000);

	setlinestyle(CENTER_LINE, 0,3); // change line thickness
	settextstyle(4, HORIZ_DIR, 1); //change character size and font
	setbkcolor(BLUE);
	
//	Create a binary tree
    
 
	
	drawTree(root, 500, 50, 170, 0, 1);

  // Close graphics mode
    getch();
    closegraph();
	
	return 0;
}

//cos(93)*7-9/(7-533*7/(9-16*3)) 
