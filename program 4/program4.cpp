#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string init = "$";

struct treetype
{
    string word;
    int count;
    treetype *left, *right;
};

void createm(treetype *&root)
{
	root= new treetype;
	root->word=init;
	root->count=0;
	root->left=NULL;
	root->right=NULL;
}
bool Emptytree (treetype *root)
{
	return root->word==init;
}
void inorder(treetype *c, ofstream &outf)
{
    if (c->left !=NULL)
        inorder (c->left,outf);
	outf << c->word << " " << c->count << endl;
    if (c->right !=NULL)
        inorder (c->right,outf);
}
void punctuation (string &word)
{
	int i;
	int len;
	string temp="";
	len=word.length();
	for (i=0;i<len;i++)
	{
		if (word[i] >= 'a' && word[i]<='z')
			temp+=word[i];
		else if (word[i] >= 'A' && word[i]<='Z')
		{
			word[i]=word[i]+32;
			temp+=word[i];

		}
	}
	word=temp;
}

void insertree(treetype *&root, string word)
{
    treetype *knew, *parent, *c;
    if (!Emptytree(root))
	{
        knew= new treetype;
        knew->word=word;
        knew->left=NULL;
        knew->right=NULL;
		knew->count=1;

	
		parent=NULL;
		c=root;
		while (c!=NULL && c->word!=word )
		{
			parent=c;
		    if (word<c->word)
			    c=c->left;
		    else
			    c=c->right;
        
		}
		if (c==NULL)
		{
			if (word<parent->word)
				parent->left=knew;
			else
				parent->right=knew;
		}
		else 
			c->count++;
	}
    else
	{
		root->word=word;
		root->count++;
	}

}

void inreadem(treetype *&root)
{
	string word;
	ifstream inf("Data.dat");
    while (!inf.eof())
{

    inf >> word;
	punctuation (word);
	if (word!="")
		insertree (root, word);
	}
}



void main()
{
	ofstream outf("Output.out");
    treetype *root;
	string word;
	createm (root);
	inreadem (root);
	inorder(root,outf);
    system("pause");
}
