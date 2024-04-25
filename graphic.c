#include<iostream>
#include<stack>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

using namespace std;

int count = 0;
bool isOperator(char x)
{
 return x == '+' || x == '-' || x == '*' || x == '/';
}
int getPriority(char x)
{
 if (x == '+' || x == '-') return 1;
 if (x == '*' || x == '/') return 2;
 return 0;
}
bool isOperand(char x)
{
 if ((x > 64 && x<91) || (x>96 && x < 123) || (x>47 && x<58)) return true;
 return false;
}
string toPostfix(string &A)
{
 stack<char> opStack;       //stack dùng de chua các toán tu ( ) + - * /
 string result = "";        //tao mot chuoi rong, chuoi này se là chuoi duoc tra ve
 for (int i = 0; i < A.size(); i++)
 {
  if (A[i]=='(')   //neu là dau mo ngoac thì thêm vào stack 
  {
   opStack.push(A[i]);
  }
  else
  {
   if (isOperand(A[i]))   //neu là toán hang a, b,c,d,e,f... thì thêm vào chuoi result
   {
    result += A[i];
   }
   else
   {
    if (isOperator(A[i]))  //neu là toán tu thì dua het nhung toán tu có do uu tiên cao hon A[i] vào result, roi thêm A[i] vào stack 
    {
     while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(A[i]))
     {
      result += opStack.top();
      opStack.pop();
     }
     opStack.push(A[i]);
    }
    else
    {
     if (A[i] == ')')
     {
      while (!opStack.empty() && opStack.top() != '(')
      {
       result += opStack.top();
       opStack.pop();
      }
      opStack.pop();
     }
    }
   }
  }
 }
 while (!opStack.empty())   //trong stack còn bao nhiêu thì cu thêm vào
 {
  result += opStack.top();
  opStack.pop();
 }
 return result; 
}
//den dây xu lý duoc xong chuoi, tuc là dua chuoi ve dang hau to, sau dây ta se dua chúng vào cây
struct Node
{
 char data;
 Node*Left;
 Node*Right;
 Node()
 {
  this->Left = this->Right = NULL;
 }
};

struct ExpressionTree
{
 Node* Root;          //cây nhi phân này chi can nam bat nút goc, các nút còn lai thì dua vào nút goc
 ExpressionTree()
 {
  this->Root = NULL;
 }
};

void LNR(Node*&R)
{
 if (R)
 {
  LNR(R->Left);
  cout << R->data << " ";
  LNR(R->Right);
 }
}

void showPostfix(Node*&R)
{
 if (R)
 {
  showPostfix(R->Left);
  showPostfix(R->Right);
  cout << R->data;
 }
}

void showPrefix(Node*&R)
{
 if (R)
 {
  cout << R->data;
  showPrefix(R->Left);
  showPrefix(R->Right);
 }
}

void addToExpression(Node*&R, string str)
{
 str = toPostfix(str);
 stack<Node*> stackNode;
 for (int i = 0; i < str.size(); i++)
 {
  if (isOperand(str[i]))
  {
   Node*P = new Node;
   P->data = str[i];
   stackNode.push(P);
  }
  else
  {
   if (isOperator(str[i]))
   {
    Node*P = new Node;
    P->data = str[i];
    P->Right = stackNode.top();
    stackNode.pop();
    P->Left = stackNode.top();
    stackNode.pop();
    stackNode.push(P);
   }
  }
 }
 R = stackNode.top();
}



// Function to create a new binary tree node


// Function to draw a binary tree recursively
int xOffpos = 50;
int lCnt = 0;
int rCnt = 0;


int childCount(struct Node* root){
	int x,y;
	if(root->Left == NULL && root->Right == NULL)
	{
		return 1;
	}else{
		if(root->Left != NULL){
			x = 1+ childCount(root->Left);
		}
		if(root->Right != NULL){
			y = 1+ childCount(root->Right);
			
		}
		
		
		if(x>=y){
			return x;
		}
		else{
			return y;
		}
	}
}

void drawTree(struct Node* root, int x, int y, int xOffset, int level) {
    if (root != NULL) {
        char buffer[10]; //chua du lieu cua NODE sau khi chuyen tu int -> string
        char check1[10];
        char check2[10];
        // Draw current node
        
        circle(x, y, 30);
        setfillstyle(SOLID_FILL, BLUE);

        
        if(root->Right != NULL && root->Left == NULL){
//        	Draw when node has only 1 child node
        	line(x,y,x,y+100);
        	
			drawTree(root->Right, x, y+100, 0, level+1);
        	
		}else{
		
		
        
        // Draw left subtree
        if (root->Left != NULL) {
        	int cntLeft = childCount(root->Left);
        	
            
//            lCnt++;
            if (level == 0 ){
            	line(x, y, x - xOffset, y + 100);
            	drawTree(root->Left, x - xOffset, y + 100, xOffset/3, level + 1);
//            	drawTree(root->Left, x - xOffpos, y + 100, xOffpos/2);
			}
			else
			{
				line(x, y, x - xOffset*(cntLeft-1), y + 100);
				drawTree(root->Left, x - xOffset*(cntLeft-1), y + 100 , xOffset, level + 1 );
//                 drawTree(root->Left, x - xOffpos, y + 100, xOffpos); 
				
			}

//             drawTree(root->Left, x - xOffset, y + 100, xOffset / 2);
//            
//            
// Draw center node
// Khi nao co struct Node -> Center thi xoa comment de chay dong lenh duoi
//if (root-> Center != NULL) {
//            line(x, y, x, y + 100);
//
//            
//            	drawTree(root->Left, x - 0, y + 100, 0, level + 1);
////            	drawTree(root->Left, x - xOffpos, y + 100, xOffpos/2);
//			

        }
        // Draw right subtree
        if (root->Right != NULL) {
        	int cntRight = childCount(root->Right);
        	
            
            
            if (level == 0 ){
            	line(x, y, x + xOffset, y + 100);
            	drawTree(root->Right, x + xOffset, y + 100, xOffset / 3, level + 1);
            	
            	
//            	drawTree(root->Right, x + xOffpos, y + 100, xOffpos / 2);
			}
			else
//			if (level == 1)
//			{
//				drawTree(root->Right, x + xOffset, y + 100, xOffset / 3 * 2, level + 1);
//			}
//			else
			{
				line(x, y, x + xOffset*(cntRight-2), y + 100);
				drawTree(root->Right, x + xOffset*(cntRight-2), y + 100 , xOffset , level + 1 );
//				drawTree(root->Right, x + xOffpos, y + 100, xOffpos );
			}
//         drawTree(root->Right, x + xOffset, y + 100, xOffset / 2);

//            
        }
    }
        sprintf(buffer, "%c", root->data); //chuyen du lieu tu data sang dang string va gan vao buffer
        fillellipse(x,y,30,30);
        
        outtextxy(x - 12, y - 10, buffer);  //in ra chuoi buffer tren man hinh
    }
}

int main()
{
 ExpressionTree ET;
 string str;
 char *b ;
 cout << "enter expression, enter '#' to exit:\n";
 char a = 'h';
 while (a != '#') 
 {
  cin >> a;
  if (a != '#') str += a;
 }
 addToExpression(ET.Root, str);
 int gd = DETECT, gm;
    initwindow(1000,1000);
//    setfillstyle(SOLID_FILL, YELLOW);
setlinestyle(CENTER_LINE, 0,3); // thay doi thickness cua line
settextstyle(4, HORIZ_DIR, 1); //thay doi kich co va font chu

setbkcolor(BLUE);


    // Create a sample binary tree
    
 
// cout << "\nLNR: \n";
// LNR(ET.Root);
// 
 drawTree(ET.Root,600, 50, 240, 0);

    // Close graphics mode
    getch();
    closegraph();
 return 0;
}

/*Exam input: 
3/7*8-6+7*9/(6*3-5*6/9)#
3/7*8-6+7*9/(6*3-5*6/(9-7*8+8/3))#
*/
