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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap *new = (TreeMap*)malloc(sizeof(TreeMap));
  if (new == NULL)return NULL;
  new->root = NULL;
  new->current = NULL;
  new->lower_than = lower_than;
  return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (tree == NULL || tree->root == NULL)return;
  Pair *pairAux = searchTreeMap(tree, key);
  if (pairAux != NULL){
    pairAux->value = value;
  }
  TreeNode *nodoNuevo = createTreeNode(key, value);
  if (nodoNuevo == NULL)return;
  TreeNode * padre = NULL;
  TreeNode *current = tree->root;
  while (current != NULL){
    padre = current;
    if (tree->lower_than(key, current->pair->key)){
      current = current->left;
    }else{
      current = current->right;
    }
    nodoNuevo->parent = padre;
    if (padre == NULL){
      tree->root = nodoNuevo;
    }else if(tree->lower_than(key, padre->pair->key)){
      padre->left = nodoNuevo;
    }else{
      padre->right = nodoNuevo;
    }
  }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if (tree == NULL || tree->root == NULL)return NULL;
  TreeNode *currentAux = tree->root;
  while (currentAux != NULL){
    if (is_equal(tree, currentAux->pair->key, key)){
      tree->current = currentAux;
      return currentAux->pair;
    }else if (tree->lower_than(key, currentAux->pair->key)){
      currentAux = currentAux->left;
    }else{
      currentAux = currentAux->right;
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
