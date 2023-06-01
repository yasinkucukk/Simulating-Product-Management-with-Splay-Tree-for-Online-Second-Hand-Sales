/*
Yasin Kucuk 150120062
Irem Aydin 150120013
*/

#include <stdio.h>
#include <stdlib.h>

struct nodeSplay *rootSplay;
int n;

struct nodeSplay
{
    int data;
    struct nodeSplay *parent;
    struct nodeSplay *left;
    struct nodeSplay *right;
};

// splay
void splay(struct nodeSplay *x)
{
    while (x->parent)
    {
        if (!x->parent->parent)
        {
            if (x->parent->left == x)
            {
                // Zig rotation
                rotate_right(x->parent);
            }
            else
            {
                // Zag rotation
                rotate_left(x->parent);
            }
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent)
        {
            // Zig-zig rotation
            rotate_right(x->parent->parent);
            rotate_right(x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent)
        {
            // Zag-zag rotation
            rotate_left(x->parent->parent);
            rotate_left(x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent)
        {
            // Zig-zag rotation
            rotate_right(x->parent);
            rotate_left(x->parent);
        }
        else
        {
            // Zag-zig rotation
            rotate_left(x->parent);
            rotate_right(x->parent);
        }
    }
}

// rotations
void rotate_left(struct nodeSplay *x)
{
    struct nodeSplay *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        rootSplay = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(struct nodeSplay *x)
{
    struct nodeSplay *y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        rootSplay = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insert(struct nodeSplay *p, int data)
{
    struct nodeSplay *newNode = (struct nodeSplay *)malloc(sizeof(struct nodeSplay));
    newNode->data = 0;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    newNode->data = data;

    if (!(rootSplay))
    {
        rootSplay = newNode;
        n = 1;
    }
    else
    {
        for (;;)
        {
            if (data < p->data)
            {
                if (p->left == NULL)
                {
                    p->left = newNode;
                    newNode->parent = p;
                    n++;
                    break;
                }
                else
                    p = p->left;
            }
            else if (data > p->data)
            {
                if (p->right == NULL)
                {
                    p->right = newNode;
                    newNode->parent = p;
                    n++;
                    break;
                }
                else
                    p = p->right;
            }
            else
            {
                break;
            }
        }
    }

    splay(newNode);
}

// search
struct nodeSplay *search(struct nodeSplay *root, int data)
{
    struct nodeSplay *p = root;
    while (p)
    {
        if (data < p->data)
        {
            p = p->left;
        }
        else if (data > p->data)
        {
            p = p->right;
        }
        else
        {
            return p;
        }
    }
    return NULL;
}

// preorder traversal with write output file
void preorder(struct nodeSplay *root, FILE *fpw)
{
    if (root != NULL)
    {
        if (root->parent != NULL)
        {
            printf(" - ");
            fprintf(fpw, " - ");
        }

        printf("%d", root->data);
        fprintf(fpw, "%d", root->data);
        preorder(root->left, fpw);
        preorder(root->right, fpw);
    }
}
// write also a output file named output.txt
int main()
{
    // get file name
    char fileNameLabels[20];
    FILE *fpw = fopen("output.txt", "w");
    
 	printf("Input file for label numbers: ");
    fprintf(fpw, "Input file for label numbers: ");
    
    scanf("%s", fileNameLabels);
    printf("\n\n");

    fprintf(fpw,"%s\n\n", fileNameLabels);
 
    FILE *fp = fopen(fileNameLabels, "r");
    

    if (fp == NULL)
    {
        printf("Cannot open the file %s", fileNameLabels);
        fprintf(fpw, "Cannot open the file %s", fileNameLabels);
        return 1;
    }


    // read the the file
    int intRead;
    while (fscanf(fp, "%d", &intRead) == 1)
    {
        insert(rootSplay, intRead);
        printf("Tree: ");
        fprintf(fpw, "Tree: ");
        preorder(rootSplay, fpw);
        printf("\n\n");
        fprintf(fpw, "\n\n");
    }
    fclose(fp);

    // get file name
    char fileNameViewed[20];
    
    printf("- - - - - - - - - - -\n\n");
    fprintf(fpw, "- - - - - - - - - - -\n\n");
    printf("Input file for viewed products: ");
    fprintf(fpw, "Input file for viewed products: ");
    
    scanf("%s", fileNameViewed);
    printf("\n\n");
    fprintf(fpw, "%s\n\n", fileNameViewed);
    
    FILE *fpr = fopen(fileNameViewed, "r");
    
    if (fpr == NULL)
    {
        printf("Cannot open the file %s", fileNameViewed);
        fprintf(fpw, "Cannot open the file %s", fileNameViewed);
        return 1;
    }
    

    // read the the file
    // search
    int intSearch;
    while (fscanf(fpr, "%d", &intSearch) == 1)
    {
        struct nodeSplay *found = search(rootSplay, intSearch);
        if (found)
        {
            splay(found);
            printf("Tree: ");
            fprintf(fpw, "Tree: ");
            preorder(rootSplay, fpw);
            printf("\n\n");
            fprintf(fpw, "\n\n");
        }
        else
        {
            printf("Node %d does not exist\n\n", intSearch);
            fprintf(fpw, "Node %d does not exist\n\n", intSearch);
        }
    }
    fclose(fpr);
    fclose(fpw);

    return 0;
}