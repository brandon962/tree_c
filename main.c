//中興大學 4105056004 資工二 許哲維 
//brandon962@gmail.com 
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 

typedef struct Node *tree_ptr;					//宣告樹的結構 
typedef struct Node 
{
	int data;									//存放數字 
	char name[100];								//存放string 
	tree_ptr parent;							//存放parent 
	tree_ptr fchild, schild, tchild;			//存放child 
	int height;									//紀錄該點數高 
};

tree_ptr node[SIZE];							//宣告樹的陣列 
int nodeCount;									//計算節點個數 
int maxHeight;									//計算樹高 
int haveString[SIZE];							//紀錄那些點有string 
int rootCount;									//記錄樹的陣列用到哪裡(哪裡還有空的記憶體可以用) 


//初始化 
tree_ptr initial();								//初始化樹 
//列印 
void ptr(tree_ptr);								//列印出樹 
//Info 
void info(tree_ptr);							//計算樹的種種(樹高,節點數.....) 
void cleanInfo();								//計算樹的種種前要先把變數歸零 
void printinfo(tree_ptr);						//列印出樹的種種 
//共用涵式 
void reName(tree_ptr);							//從新編碼樹的數字(在新增或刪除節點後數字需改變) 
int find(int);									//找尋目標的節點在樹的哪裡 
//insert
void insert(tree_ptr, int);						//新增節點 
//delete 
void del(tree_ptr, int);						//刪除的第一個步驟 先刪除parent到child的關系 
void delAll(tree_ptr);							//剩下的用遞迴刪除 
//string的處裡 
void stringAppend();							//將輸入字串加在原本字串後 
void stringDelete();							//刪除字串 
void stringModify();							//修改字串 
void view();									//檢視字串 


int main(int argc, char *argv[]) 
{
	tree_ptr root;								//宣告樹根 
	root = initial();							//初始化 
	
	char command[20];							//指令 
	int com;									//同上 
	
	printf("初始化目錄表\n");
	prt(root);								//列印樹當前的樣子 
	printf("\n");
	
	printf("請輸入指令(輸入cList可以查詢命令表):\n");				//貼心設計
	 
	while(scanf("%s", &command) != EOF)							//可重複輸入指令 
	{
		if(strcmp("cList", command) == 0)						//設定變數com, 等毀要用com來switch 
			com = 999;	
		else if(strcmp("Info", command) == 0)
			com = 1;
		else if(strcmp("Insert", command) == 0)
			com = 2;
		else if(strcmp("Delete", command) == 0)
			com = 3;
		else if(strcmp("stringAppend", command) == 0)
			com = 4;
		else if(strcmp("stringDelete", command) == 0)
			com = 5;
		else if(strcmp("stringModify", command) == 0)
			com = 6;
		else if(strcmp("View", command) == 0)
			com = 7;
		else
			com = 0;
		
		
		switch(com)												//判斷輸入的命令是什麼 
		{
			int input;
			case 1:												//Info 
				cleanInfo();									//清除目前記錄樹的種種 
				info(root);										//從新計算 
				printInfo(root);								//列印出 
				system("PAUSE");
				break;
			
			case 2:												//Insert
				printf("輸入欲加file的點 : ");
				scanf("%d", &input);
				insert(root, input);							//加入節點 
				system("PAUSE");
				break;
				
			case 3:												//Delete 
				printf("輸入欲刪除的file : ");					
				scanf("%d", &input);
				del(root, input);								//刪除節點 
				system("PAUSE");
				break;
				
			case 4:												//stringAppend 
				stringAppend();									//將輸入的字串加在原字串後 
				system("PAUSE");
				break;
				
			case 5:												//stringDelete
				stringDelete();									//刪除原字串 
				system("PAUSE");
				break;
				
			case 6:												//stringModify
				stringModify();									//修改原字串 
				system("PAUSE");
				break;
				
			case 7:												//View 
				view();											//檢視原字串 
				system("PAUSE");
				break;
			
			case 999:											//CList 
				system("cls");									//顯示命令集 
				printf("cList : 查詢命令表\n");
				printf("Info : Show出樹高,檔案個數,當前目錄表,那些節點有存string(若無則顯示無資料)\n");
				printf("Insert : 新增file(到最右子點),超過3個則無法新增\n");
				printf("Delete : 刪除含該目錄下的目錄 \n");
				printf("stringAppend : 先輸入欲插入的file, 輸入欲儲存的string\n");
				printf("stringDelete : 輸入欲刪除的string在哪個file\n");
				printf("stringModify : 輸入欲修改的file, Show出存入的string,並且可供修改, 修改結束後存入file中\n");
				printf("View : 輸入欲檢視的file,然後show出string(若是沒有string則顯示無資料)");
				system("PAUSE");
				break;
			
			default:											//輸入非正常命令 
				printf("輸入錯誤\n");
				system("PAUSE");
		}
		
		
		system("cls");
		prt(root);
		printf("\n請輸入下個指令(輸入cList可以查詢命令表)\n"); 
	}
	return 0;
}

tree_ptr initial()								//初始化樹 
{
	int i;										//初始化樹的陣列 
	for (i = 0; i < SIZE; i++)
	{
		node[i] = malloc(sizeof(*node[i]));		//要記憶體空間 
		node[i]->parent = NULL;					//初始化剩下的數值 
		node[i]->fchild = NULL;
		node[i]->schild = NULL;
		node[i]->tchild = NULL;
		node[i]->name[0] = '\0';
	}
	
	//以下都是初始化 
	node[0]->data = 1;
	node[0]->fchild = node[2];
	node[0]->schild = node[3];
	node[0]->height = 1;
	
	node[2]->data = 2;
	node[2]->parent = node[0];
	node[2]->height = node[2]->parent->height + 1;

	node[3]->data = 3;
	node[3]->parent = node[0];
	node[3]->name[0] = 'W'; node[3]->name[1] = 'o'; node[3]->name[2] = 'r'; node[3]->name[3] = 'l'; node[3]->name[4] = 'd'; node[3]->name[5] = '!'; node[3]->name[6] = '\0';
	node[3]->fchild = node[4];
	node[3]->schild = node[5];
	node[3]->tchild = node[6];
	node[3]->height = node[3]->parent->height + 1;
	
	node[4]->data = 4;
	node[4]->parent = node[3];
	node[4]->fchild = node[7];
	node[4]->schild = node[8];
	node[4]->height = node[4]->parent->height + 1;
	
	node[5]->data = 5;
	node[5]->parent = node[3];
	node[5]->height = node[5]->parent->height + 1;
	
	node[6]->data = 6;
	node[6]->parent = node[3];
	node[6]->name[0] = 'H'; node[6]->name[1] = 'e'; node[6]->name[2] = 'l'; node[6]->name[3] = 'l'; node[6]->name[4] = 'o'; node[6]->name[5] = '\0'; 
	node[6]->height = node[6]->parent->height + 1;
	
	node[7]->data = 7;
	node[7]->parent = node[4];
	node[7]->height = node[7]->parent->height + 1;
	
	node[8]->data = 8;
	node[8]->parent = node[4];
	node[8]->height = node[8]->parent->height + 1;
	
	rootCount = 8;								//紀錄目前陣列用到的位置 
	return node[0];
}

void prt(tree_ptr ptr)							//列印出樹(遞迴) 
{
	if(ptr)										//如果該點不存在就直接return 遞迴終點 
	{
		printf("%d", ptr->data);				//列印該點 
		if(ptr->fchild)							 
		{
			printf("[");						//如果有孩子才需要印中括號 
			prt(ptr->fchild);					//遞迴,如果孩子不存在,在進去時會直結束 
			prt(ptr->schild);
			prt(ptr->tchild);
			printf("]");
		}
	}
	return;
}

void cleanInfo()								//計算樹的種種前要先把變數歸零 
{
	maxHeight = 0;								//將所有便樹歸零 
	nodeCount = 0;
	int i;
	for (i = 0; i < SIZE; i++)
		haveString[i] = 0;
	return;
}

void info(tree_ptr ptr)							//計算樹的種種(樹高,節點數.....) (遞迴) 
{
	if (ptr)									//如果該點存在 
	{
		nodeCount++;							//節點個數加一 
		
		if (ptr->height > maxHeight)			//檢查該點高度是否比目前最大樹高還大 
			maxHeight = ptr->height;
			
		if (ptr->name[0] != '\0')				//檢查是否有string 
			haveString[ptr->data] = 1;
		
		if (ptr->fchild)						//遞迴:往孩子下去找 
		{
			info(ptr->fchild);
			info(ptr->schild);
			info(ptr->tchild);
		}
	}
	return;
}

void printInfo(tree_ptr ptr)					//列印出樹的種種 
{
	printf("樹高 = %d\n", maxHeight);			//列印出該列印的值 
	printf("node個數 = %d\n", nodeCount);
	prt(ptr);
	printf("\n那些目錄有string = ");
	int i;
	for(i = 0; i < SIZE; i++)
	{
		if(haveString[i] == 1)
			printf("%d, ", i);
	}
	printf("\b\b  \n");							//把最後的","給刪除
	
	return; 
}

void reName(tree_ptr ptr)						//從新編碼樹的數字(在新增或刪除節點後數字需改變) 
{
	tree_ptr queue[SIZE];						//建立一個queue方便一層一層的往下找(這樣編起號來才會正確) 
	queue[1] = ptr;								//因為編號從1開始, queue[0]直接放棄 
	int i, end = 2;								//end 紀錄queue的尾巴 
	
	for(i = 1; i < end; i++)					// 開始讀寫queue 
	{
		queue[i]->data = i;						//開始從新編碼 
		if (queue[i]->fchild)					//若有孩子就把它放在queue的尾吧,這樣就會按照樹的高度往下讀 
		{
			queue[end] = queue[i]->fchild;
			end++;
		}
		if (queue[i]->schild)
		{
			queue[end] = queue[i]->schild;
			end++;
		}
		if (queue[i]->tchild)
		{
			queue[end] = queue[i]->tchild;
			end++;
		}
	}
	return;
}

int find(int input)								//找尋目標的節點在樹的哪裡 
{												
	int i, which = 999;							//input為輸入的點 ,which是作為檢查用,檢查該點是否存在,不存在就會維持在999 
	for(i = 0; i < SIZE; i++)					//透過一開始建立的node陣列來檢索 
	{
		if(node[i]->data == input)
		{
			which = i;
			return i;							//若找到該點就回傳該點在node的位置 
		}
	}
	if (which == 999)							//若which還是999表示沒有找到->輸入錯誤 
	{
		printf("輸入錯誤\n");
		return which;
	}
}

void insert(tree_ptr ptr, int input)			//新增節點 
{
	int which;									//which接取find涵式回傳的值 
	
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	rootCount++;
	if (node[which]->fchild == NULL)								//若fchild是空的就填入
		node[which]->fchild = node[rootCount];	
	else if (node[which]->schild == NULL)							//fchild有值,schild是空的 
		node[which]->schild = node[rootCount];
	else if (node[which]->tchild == NULL)							//fchild, schild有值, tchild是空的 
		node[which]->tchild = node[rootCount];
	else															//若三個都有值,表示該點滿了不能在加了 
	{
		rootCount--;
		printf("這個file滿了,請換一個");
		return;
	}
	node[rootCount]->parent = node[which];							//建立通往家長的線 
	node[rootCount]->data = 999;									//新增節點的暫時值(不是很重要,因為會呼叫reName()把這個值從新編碼) 
	node[rootCount]->height = node[which]->height + 1;				//計算該點樹高並紀錄 
	
	//維護 (把info從新計算; 檢查是否有值是錯的(EX:999之類的)) 
	cleanInfo();													
	info(ptr);
	reName(ptr);			
	
	//列印結果 
	prt(ptr);
	printf("\n");
	return;
	
}

void del(tree_ptr ptr, int input)				//刪除的第一個步驟 先刪除parent到child的關系 
{
	if(input == 1)								//題目規定不能刪除樹根 
	{
		printf("無法刪除樹根\n");
		return;
	}
	
	int which;									//which接取find涵式回傳的值 
	
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	//若要刪除的點是第一個,就把第二個點壓過第一個,第三個點壓過第二個,刪除第三個的值 
	if(node[which]->parent->fchild == node[which])						
	{
		node[which]->parent->fchild = node[which]->parent->schild;
		node[which]->parent->schild = node[which]->parent->tchild;
		node[which]->parent->tchild = NULL;
	}
	//若要刪除的點是第二個,就把第三個點壓過第二個,刪除第三個的值
	else if(node[which]->parent->schild == node[which])
	{
		node[which]->parent->schild = node[which]->parent->tchild;
		node[which]->parent->tchild = NULL;
	}
	//若要刪除的點是第三個,就直接刪除,不用再動位置了 
	else if(node[which]->parent->tchild == node[which])
		node[which]->parent->tchild = NULL;
	
	delAll(node[which]); 						//接下來把該點下的所有點都給刪了 
	reName(ptr);								//因為刪除的關係,所以編碼會亂掉,要從新編碼 
	prt(ptr);									//列印出新的樹 
	return;
}

void delAll(tree_ptr ptr)						//剩下的用遞迴刪除 
{
	if(ptr)										//如果該點存在 
	{
		if(ptr->fchild)							//如果該該點的孩子存在 
		{
			delAll(ptr->fchild);				//先從最下面的開始刪除,所以會一直呼叫直到沒有孩子為止 
			delAll(ptr->schild);
			delAll(ptr->tchild);
		}
		ptr->data = NULL;						//把她所有內容都刪除(NULL) 
		ptr->height = NULL;
		ptr->parent = NULL;
		ptr->fchild = NULL;
		ptr->schild = NULL;
		ptr->tchild = NULL;
		ptr->name[0] = '\0';
	}
	return;
}

void stringAppend()								//將輸入字串加在原本字串後 
{
	int input;									//接下來要接收的變數 
	char name[100];
	
	printf("輸入欲輸入欲插入的file : ");
	scanf("%d", &input);
	
	int which;									//which接取find涵式回傳的值 
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	printf("輸入欲儲存的string : ");
	scanf("%s", name);
	
	strcat(node[which]->name, name);			//透過strcat將輸入的字串加在源字串後 
	
	return;
}

void stringDelete()								//刪除字串
{
	int input;									//接下來要接收的變數 
	printf("輸入欲刪除的string在哪個file\n");
	scanf("%d", &input);
	
	int which;									//which接取find涵式回傳的值 
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	node[which]->name[0] = '\0';				//將字串第一個位置的內容設為\0即可刪除該字串 
	
	return;
}

void stringModify()								//修改字串
{
	int input;									//接下來要接收的變數 
	printf("輸入欲修改的file : ");
	scanf("%d", &input);
	
	int which;									//which接取find涵式回傳的值 
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	char ch;											//接下來用來接收每次鍵盤輸入的內容 
	int j;									
 	for(j = 0; j < sizeof(node[which]->name); j++)		//尋找字串的長度 
  		if(node[which]->name[j] == '\0')
   			break;
   			
 	printf("\r欲儲存的string : %s", node[which]->name);					//將原字串列印出 
	do
	{
    	ch = getche();									//接收鍵盤輸入內容,並"馬上"將內容列印在螢幕上 
      
   		node[which]->name[j] = ch;						//將剛剛接收到的內容存到原字串裡面 
   		if (ch == '\b')									//若鍵盤輸入為到退件時 
      	{
       		node[which]->name[j-1] = NULL;				//字串最後一個字要刪除 
       		printf(" \b");								//並利用空白在顯示上蓋掉原字元 
       		j = j -2;									//最後一個的位置要調整 
			if(j<-1)									//不能倒退超過原本字串長度 
				break;								
   		}
      	j++;											//調整最後的位置 
      
  	}
	while(ch!='\r');									//輸入enter時結束這個do while 
	node[which]->name[j-1] = '\0';						//並在字串最後補回\0 
  	printf("\r\n更改結果為 : %s", node[which]->name);	//將結果列印出來 
  	printf("\n");

  	return;
}

void view()										//檢視字串 
{
	int input;									//接下來要接收的變數 
	printf("輸入欲檢視的file : ");
	scanf("%d", &input);
	
	int which;									//which接取find涵式回傳的值 
	which = find(input);						//呼叫find涵式 
	if (which == 999)							//若回傳999表示輸入有誤,直接結束涵式 
		return;
	
	printf("內容為 : ");
	if(node[which]->name[0] == '\0')			//如果name[0]是\0表示該字串是空的 
		printf("無資料\n");
	else
		printf("%s\n", node[which]->name);		//列印出該值 
	
	return;
}
