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
  
      if (tree == NULL) return;

    Pair * pair = searchTreeMap(tree, key);
    if (pair != NULL) {
        pair->value = value;
        return;
    }

    TreeNode * nodoNuevo = createTreeNode(key, value);
    if (nodoNuevo == NULL) return;

    TreeNode * parent = NULL;
    TreeNode * current = tree->root;
    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    nodoNuevo->parent = parent;
    if (parent == NULL) {
        tree->root = nodoNuevo;
    } else if (tree->lower_than(key, parent->pair->key)) {
        parent->left = nodoNuevo;
    } else {
        parent->right = nodoNuevo;
    }

    tree->current = nodoNuevo;
}

TreeNode * minimum(TreeNode * x){
  if (x == NULL)return NULL;
  while (x->left != NULL){
    x = x->left;
    if (x->left == NULL)break;
  }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if (tree == NULL || tree->root == NULL || node == NULL) return;

    if (node->left == NULL && node->right == NULL) {
        if (node->parent == NULL) { 
            tree->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        free(node->pair);
        free(node);
    }

    else if (node->left == NULL || node->right == NULL) {
        TreeNode * child = (node->left != NULL) ? node->left : node->right;
        if (node->parent == NULL) { 
            tree->root = child;
            child->parent = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = child;
            child->parent = node->parent;
        } else {
            node->parent->right = child;
            child->parent = node->parent;
        }
        free(node->pair);
        free(node);
    }

    else {
        TreeNode * minNode = minimum(node->right);
        node->pair->key = minNode->pair->key;
        node->pair->value = minNode->pair->value;
        removeNode(tree, minNode);
    }
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
  if (tree == NULL || tree->root == NULL) return NULL;
  TreeNode *current = tree->root;
  while (current->left != NULL) {
      current = current->left;
  }
  tree->current = current;
  return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree == NULL || tree->root == NULL) return NULL;
    if (tree->current == NULL) 
        tree->current = tree->root;
        while (tree->current->left != NULL) {
            tree->current = tree->current->left;
        }
    } else if (tree->current->right != NULL) {
        tree->current = tree->current->right;
        while (tree->current->left != NULL) {
            tree->current = tree->current->left;
        }
    } else {
        TreeNode * parent = tree->current->parent;
        while (parent != NULL && tree->current == parent->right) {
            tree->current = parent;
            parent = parent->parent;
        }
        tree->current = parent;
    }

    if (tree->current == NULL) return NULL;
    return tree->current->pair;
}
