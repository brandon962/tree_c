//�����j�� 4105056004 ��u�G �\���� 
//brandon962@gmail.com 
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 

typedef struct Node *tree_ptr;					//�ŧi�𪺵��c 
typedef struct Node 
{
	int data;									//�s��Ʀr 
	char name[100];								//�s��string 
	tree_ptr parent;							//�s��parent 
	tree_ptr fchild, schild, tchild;			//�s��child 
	int height;									//�������I�ư� 
};

tree_ptr node[SIZE];							//�ŧi�𪺰}�C 
int nodeCount;									//�p��`�I�Ӽ� 
int maxHeight;									//�p��� 
int haveString[SIZE];							//���������I��string 
int rootCount;									//�O���𪺰}�C�Ψ����(�����٦��Ū��O����i�H��) 


//��l�� 
tree_ptr initial();								//��l�ƾ� 
//�C�L 
void ptr(tree_ptr);								//�C�L�X�� 
//Info 
void info(tree_ptr);							//�p��𪺺غ�(��,�`�I��.....) 
void cleanInfo();								//�p��𪺺غثe�n�����ܼ��k�s 
void printinfo(tree_ptr);						//�C�L�X�𪺺غ� 
//�@�β[�� 
void reName(tree_ptr);							//�q�s�s�X�𪺼Ʀr(�b�s�W�ΧR���`�I��Ʀr�ݧ���) 
int find(int);									//��M�ؼЪ��`�I�b�𪺭��� 
//insert
void insert(tree_ptr, int);						//�s�W�`�I 
//delete 
void del(tree_ptr, int);						//�R�����Ĥ@�ӨB�J ���R��parent��child�����t 
void delAll(tree_ptr);							//�ѤU���λ��j�R�� 
//string���B�� 
void stringAppend();							//�N��J�r��[�b�쥻�r��� 
void stringDelete();							//�R���r�� 
void stringModify();							//�ק�r�� 
void view();									//�˵��r�� 


int main(int argc, char *argv[]) 
{
	tree_ptr root;								//�ŧi��� 
	root = initial();							//��l�� 
	
	char command[20];							//���O 
	int com;									//�P�W 
	
	printf("��l�ƥؿ���\n");
	prt(root);								//�C�L���e���ˤl 
	printf("\n");
	
	printf("�п�J���O(��JcList�i�H�d�ߩR�O��):\n");				//�K�߳]�p
	 
	while(scanf("%s", &command) != EOF)							//�i���ƿ�J���O 
	{
		if(strcmp("cList", command) == 0)						//�]�w�ܼ�com, �����n��com��switch 
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
		
		
		switch(com)												//�P�_��J���R�O�O���� 
		{
			int input;
			case 1:												//Info 
				cleanInfo();									//�M���ثe�O���𪺺غ� 
				info(root);										//�q�s�p�� 
				printInfo(root);								//�C�L�X 
				system("PAUSE");
				break;
			
			case 2:												//Insert
				printf("��J���[file���I : ");
				scanf("%d", &input);
				insert(root, input);							//�[�J�`�I 
				system("PAUSE");
				break;
				
			case 3:												//Delete 
				printf("��J���R����file : ");					
				scanf("%d", &input);
				del(root, input);								//�R���`�I 
				system("PAUSE");
				break;
				
			case 4:												//stringAppend 
				stringAppend();									//�N��J���r��[�b��r��� 
				system("PAUSE");
				break;
				
			case 5:												//stringDelete
				stringDelete();									//�R����r�� 
				system("PAUSE");
				break;
				
			case 6:												//stringModify
				stringModify();									//�ק��r�� 
				system("PAUSE");
				break;
				
			case 7:												//View 
				view();											//�˵���r�� 
				system("PAUSE");
				break;
			
			case 999:											//CList 
				system("cls");									//��ܩR�O�� 
				printf("cList : �d�ߩR�O��\n");
				printf("Info : Show�X��,�ɮ׭Ӽ�,��e�ؿ���,���Ǹ`�I���sstring(�Y�L�h��ܵL���)\n");
				printf("Insert : �s�Wfile(��̥k�l�I),�W�L3�ӫh�L�k�s�W\n");
				printf("Delete : �R���t�ӥؿ��U���ؿ� \n");
				printf("stringAppend : ����J�����J��file, ��J���x�s��string\n");
				printf("stringDelete : ��J���R����string�b����file\n");
				printf("stringModify : ��J���ק諸file, Show�X�s�J��string,�åB�i�ѭק�, �קﵲ����s�Jfile��\n");
				printf("View : ��J���˵���file,�M��show�Xstring(�Y�O�S��string�h��ܵL���)");
				system("PAUSE");
				break;
			
			default:											//��J�D���`�R�O 
				printf("��J���~\n");
				system("PAUSE");
		}
		
		
		system("cls");
		prt(root);
		printf("\n�п�J�U�ӫ��O(��JcList�i�H�d�ߩR�O��)\n"); 
	}
	return 0;
}

tree_ptr initial()								//��l�ƾ� 
{
	int i;										//��l�ƾ𪺰}�C 
	for (i = 0; i < SIZE; i++)
	{
		node[i] = malloc(sizeof(*node[i]));		//�n�O����Ŷ� 
		node[i]->parent = NULL;					//��l�ƳѤU���ƭ� 
		node[i]->fchild = NULL;
		node[i]->schild = NULL;
		node[i]->tchild = NULL;
		node[i]->name[0] = '\0';
	}
	
	//�H�U���O��l�� 
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
	
	rootCount = 8;								//�����ثe�}�C�Ψ쪺��m 
	return node[0];
}

void prt(tree_ptr ptr)							//�C�L�X��(���j) 
{
	if(ptr)										//�p�G���I���s�b�N����return ���j���I 
	{
		printf("%d", ptr->data);				//�C�L���I 
		if(ptr->fchild)							 
		{
			printf("[");						//�p�G���Ĥl�~�ݭn�L���A�� 
			prt(ptr->fchild);					//���j,�p�G�Ĥl���s�b,�b�i�h�ɷ|������ 
			prt(ptr->schild);
			prt(ptr->tchild);
			printf("]");
		}
	}
	return;
}

void cleanInfo()								//�p��𪺺غثe�n�����ܼ��k�s 
{
	maxHeight = 0;								//�N�Ҧ��K���k�s 
	nodeCount = 0;
	int i;
	for (i = 0; i < SIZE; i++)
		haveString[i] = 0;
	return;
}

void info(tree_ptr ptr)							//�p��𪺺غ�(��,�`�I��.....) (���j) 
{
	if (ptr)									//�p�G���I�s�b 
	{
		nodeCount++;							//�`�I�Ӽƥ[�@ 
		
		if (ptr->height > maxHeight)			//�ˬd���I���׬O�_��ثe�̤j���٤j 
			maxHeight = ptr->height;
			
		if (ptr->name[0] != '\0')				//�ˬd�O�_��string 
			haveString[ptr->data] = 1;
		
		if (ptr->fchild)						//���j:���Ĥl�U�h�� 
		{
			info(ptr->fchild);
			info(ptr->schild);
			info(ptr->tchild);
		}
	}
	return;
}

void printInfo(tree_ptr ptr)					//�C�L�X�𪺺غ� 
{
	printf("�� = %d\n", maxHeight);			//�C�L�X�ӦC�L���� 
	printf("node�Ӽ� = %d\n", nodeCount);
	prt(ptr);
	printf("\n���ǥؿ���string = ");
	int i;
	for(i = 0; i < SIZE; i++)
	{
		if(haveString[i] == 1)
			printf("%d, ", i);
	}
	printf("\b\b  \n");							//��̫᪺","���R��
	
	return; 
}

void reName(tree_ptr ptr)						//�q�s�s�X�𪺼Ʀr(�b�s�W�ΧR���`�I��Ʀr�ݧ���) 
{
	tree_ptr queue[SIZE];						//�إߤ@��queue��K�@�h�@�h�����U��(�o�˽s�_���Ӥ~�|���T) 
	queue[1] = ptr;								//�]���s���q1�}�l, queue[0]������� 
	int i, end = 2;								//end ����queue������ 
	
	for(i = 1; i < end; i++)					// �}�lŪ�gqueue 
	{
		queue[i]->data = i;						//�}�l�q�s�s�X 
		if (queue[i]->fchild)					//�Y���Ĥl�N�⥦��bqueue�����a,�o�˴N�|���Ӿ𪺰��ש��UŪ 
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

int find(int input)								//��M�ؼЪ��`�I�b�𪺭��� 
{												
	int i, which = 999;							//input����J���I ,which�O�@���ˬd��,�ˬd���I�O�_�s�b,���s�b�N�|�����b999 
	for(i = 0; i < SIZE; i++)					//�z�L�@�}�l�إߪ�node�}�C���˯� 
	{
		if(node[i]->data == input)
		{
			which = i;
			return i;							//�Y�����I�N�^�Ǹ��I�bnode����m 
		}
	}
	if (which == 999)							//�Ywhich�٬O999��ܨS�����->��J���~ 
	{
		printf("��J���~\n");
		return which;
	}
}

void insert(tree_ptr ptr, int input)			//�s�W�`�I 
{
	int which;									//which����find�[���^�Ǫ��� 
	
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	rootCount++;
	if (node[which]->fchild == NULL)								//�Yfchild�O�Ū��N��J
		node[which]->fchild = node[rootCount];	
	else if (node[which]->schild == NULL)							//fchild����,schild�O�Ū� 
		node[which]->schild = node[rootCount];
	else if (node[which]->tchild == NULL)							//fchild, schild����, tchild�O�Ū� 
		node[which]->tchild = node[rootCount];
	else															//�Y�T�ӳ�����,��ܸ��I���F����b�[�F 
	{
		rootCount--;
		printf("�o��file���F,�д��@��");
		return;
	}
	node[rootCount]->parent = node[which];							//�إ߳q���a�����u 
	node[rootCount]->data = 999;									//�s�W�`�I���Ȯɭ�(���O�ܭ��n,�]���|�I�sreName()��o�ӭȱq�s�s�X) 
	node[rootCount]->height = node[which]->height + 1;				//�p����I�𰪨ì��� 
	
	//���@ (��info�q�s�p��; �ˬd�O�_���ȬO����(EX:999������)) 
	cleanInfo();													
	info(ptr);
	reName(ptr);			
	
	//�C�L���G 
	prt(ptr);
	printf("\n");
	return;
	
}

void del(tree_ptr ptr, int input)				//�R�����Ĥ@�ӨB�J ���R��parent��child�����t 
{
	if(input == 1)								//�D�سW�w����R����� 
	{
		printf("�L�k�R�����\n");
		return;
	}
	
	int which;									//which����find�[���^�Ǫ��� 
	
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	//�Y�n�R�����I�O�Ĥ@��,�N��ĤG���I���L�Ĥ@��,�ĤT���I���L�ĤG��,�R���ĤT�Ӫ��� 
	if(node[which]->parent->fchild == node[which])						
	{
		node[which]->parent->fchild = node[which]->parent->schild;
		node[which]->parent->schild = node[which]->parent->tchild;
		node[which]->parent->tchild = NULL;
	}
	//�Y�n�R�����I�O�ĤG��,�N��ĤT���I���L�ĤG��,�R���ĤT�Ӫ���
	else if(node[which]->parent->schild == node[which])
	{
		node[which]->parent->schild = node[which]->parent->tchild;
		node[which]->parent->tchild = NULL;
	}
	//�Y�n�R�����I�O�ĤT��,�N�����R��,���ΦA�ʦ�m�F 
	else if(node[which]->parent->tchild == node[which])
		node[which]->parent->tchild = NULL;
	
	delAll(node[which]); 						//���U�ӧ���I�U���Ҧ��I�����R�F 
	reName(ptr);								//�]���R�������Y,�ҥH�s�X�|�ñ�,�n�q�s�s�X 
	prt(ptr);									//�C�L�X�s���� 
	return;
}

void delAll(tree_ptr ptr)						//�ѤU���λ��j�R�� 
{
	if(ptr)										//�p�G���I�s�b 
	{
		if(ptr->fchild)							//�p�G�Ӹ��I���Ĥl�s�b 
		{
			delAll(ptr->fchild);				//���q�̤U�����}�l�R��,�ҥH�|�@���I�s����S���Ĥl���� 
			delAll(ptr->schild);
			delAll(ptr->tchild);
		}
		ptr->data = NULL;						//��o�Ҧ����e���R��(NULL) 
		ptr->height = NULL;
		ptr->parent = NULL;
		ptr->fchild = NULL;
		ptr->schild = NULL;
		ptr->tchild = NULL;
		ptr->name[0] = '\0';
	}
	return;
}

void stringAppend()								//�N��J�r��[�b�쥻�r��� 
{
	int input;									//���U�ӭn�������ܼ� 
	char name[100];
	
	printf("��J����J�����J��file : ");
	scanf("%d", &input);
	
	int which;									//which����find�[���^�Ǫ��� 
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	printf("��J���x�s��string : ");
	scanf("%s", name);
	
	strcat(node[which]->name, name);			//�z�Lstrcat�N��J���r��[�b���r��� 
	
	return;
}

void stringDelete()								//�R���r��
{
	int input;									//���U�ӭn�������ܼ� 
	printf("��J���R����string�b����file\n");
	scanf("%d", &input);
	
	int which;									//which����find�[���^�Ǫ��� 
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	node[which]->name[0] = '\0';				//�N�r��Ĥ@�Ӧ�m�����e�]��\0�Y�i�R���Ӧr�� 
	
	return;
}

void stringModify()								//�ק�r��
{
	int input;									//���U�ӭn�������ܼ� 
	printf("��J���ק諸file : ");
	scanf("%d", &input);
	
	int which;									//which����find�[���^�Ǫ��� 
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	char ch;											//���U�ӥΨӱ����C����L��J�����e 
	int j;									
 	for(j = 0; j < sizeof(node[which]->name); j++)		//�M��r�ꪺ���� 
  		if(node[which]->name[j] == '\0')
   			break;
   			
 	printf("\r���x�s��string : %s", node[which]->name);					//�N��r��C�L�X 
	do
	{
    	ch = getche();									//������L��J���e,��"���W"�N���e�C�L�b�ù��W 
      
   		node[which]->name[j] = ch;						//�N��豵���쪺���e�s���r��̭� 
   		if (ch == '\b')									//�Y��L��J����h��� 
      	{
       		node[which]->name[j-1] = NULL;				//�r��̫�@�Ӧr�n�R�� 
       		printf(" \b");								//�çQ�Ϊťզb��ܤW�\����r�� 
       		j = j -2;									//�̫�@�Ӫ���m�n�վ� 
			if(j<-1)									//����˰h�W�L�쥻�r����� 
				break;								
   		}
      	j++;											//�վ�̫᪺��m 
      
  	}
	while(ch!='\r');									//��Jenter�ɵ����o��do while 
	node[which]->name[j-1] = '\0';						//�æb�r��̫�ɦ^\0 
  	printf("\r\n��ﵲ�G�� : %s", node[which]->name);	//�N���G�C�L�X�� 
  	printf("\n");

  	return;
}

void view()										//�˵��r�� 
{
	int input;									//���U�ӭn�������ܼ� 
	printf("��J���˵���file : ");
	scanf("%d", &input);
	
	int which;									//which����find�[���^�Ǫ��� 
	which = find(input);						//�I�sfind�[�� 
	if (which == 999)							//�Y�^��999��ܿ�J���~,���������[�� 
		return;
	
	printf("���e�� : ");
	if(node[which]->name[0] == '\0')			//�p�Gname[0]�O\0��ܸӦr��O�Ū� 
		printf("�L���\n");
	else
		printf("%s\n", node[which]->name);		//�C�L�X�ӭ� 
	
	return;
}
