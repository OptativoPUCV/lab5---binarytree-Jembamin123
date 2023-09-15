#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)){
  TreeMap* newMap=(TreeMap*)malloc(sizeof(TreeMap));
  newMap->root=NULL;
  newMap->current=NULL;
  newMap->lower_than=lower_than;
  return newMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {    
  TreeNode* nodoAct=tree->root;
  TreeNode* newNode=createTreeNode(key,value);

  while(1){
    if(is_equal(tree,key,nodoAct->pair->key)){
      return;
    }
    else{
      if(tree->lower_than(nodoAct->pair->key,key)){
        if(nodoAct->right==NULL){
          nodoAct->right=newNode;
          newNode->parent=nodoAct;
          tree->current=newNode;
          return;
        }
        else{
          nodoAct=nodoAct->right;
        }
      }
      else{
        if(nodoAct->left==NULL){
          nodoAct->left=newNode;
          newNode->parent=nodoAct;
          tree->current=newNode;
          return;
        }
        else{
          nodoAct=nodoAct->left;
        }
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){    
  TreeNode* nodoAct = x;
    while(nodoAct!=NULL && nodoAct->left!=NULL){
      nodoAct = nodoAct->left;
    }
  return nodoAct;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(tree==NULL){
    return;
  }
  //caso0
  if (node->left==NULL && node->right==NULL){
    if(node->parent!=NULL){
      if (node->parent->left==node){
        node->parent->left=NULL;
      } 
      else{
        node->parent->right=NULL;
        }
    } 
    else{
      tree->root=NULL;
    }
  }
  else{
    if(node->left==0||node->right==0){
      //caso1
      TreeNode* son=node->right;
      if(node->parent!=NULL){
        if(node->parent->left==node){
          node->parent->left=son;
        }
        else{
          node->parent->right=son;
        }
        son->parent=node->parent;
      }
      else{
        tree->root=son;
        son->parent=NULL;
      }
    }
    else{
      if(node->right==NULL){
        TreeNode *son=node->left;
        if(node->parent!=NULL){
          if(node->parent->left==node){
            node->parent->left =son;
          } 
          else{
            node->parent->right=son;
          }
          son->parent=node->parent;
        } 
        else{
          tree->root=son;
          son->parent=NULL;
        }
      }
      else{
        TreeNode* min=minimun(node->right);
        void* auxValue=node->pair->value;
        void* auxKey=node->pair->key; 
        node->pair->key=min->pair->key;
        node->pair->value=min->pair->value;

        min->pair->value=auxValue;
        min->pair->key=auxKey;
        
        removeNode(tree,min);
      }
    }
  }
  free(node);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode* nodoActual= tree->root;  
  while(nodoActual!=NULL){
    if(is_equal(tree,nodoActual->pair->key,key)){
      tree->current=nodoActual;
      return tree->current->pair;
    }
    else{
      if(tree->lower_than(key,nodoActual->pair->key)){
        nodoActual=nodoActual->left;
      }
      else{
        nodoActual=nodoActual->right;
      } 
    }    
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
