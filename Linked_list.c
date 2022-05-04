#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
        int val;
        float weigth;
        bool using;
} Datanode;

typedef struct node {
        struct node *next;
        int size;
        int id;

        //void (*push)();
        Datanode vals;
} node;

node *create_node();

void push(node *list, Datanode vals) {
        printf("\x1b[32mPUSHED [ %d ] VALUE to array\n\x1b[0m", vals.val);
        list->size++;
        while (list->next != NULL)
                 list = list->next;

        node *new_node = create_node();
                new_node->id = list->id+1;
                list->next = new_node;

  list->next->vals.val = vals.val;
  new_node->vals.weigth = vals.weigth;
  new_node->vals.using = vals.using;

        // list->id = (list->id == 0)*(list->id+1);  // if (list->id != 0) list->id++;    But not necessary anymore...
}

void fix_info(node *head){
        int num_size[2] = {0, head->size};  // (num, previous_size)

        head = head->next;  // Starting from the second one.

        while (head != NULL) {
                puts("FOI AQUI EM");
                head->id = num_size[0];
                num_size[1] -= 1;
                head->size = num_size[1];
                head = head->next;
                num_size[0]++;
        }
        return;
}

node *pop(node *head)
{
        if (head->next == NULL || head == NULL){
                fprintf(stderr, "HOUVE UMA TENTATIVA DE ACESSO SEM SUCESSO NO NODE... \x1b[32mFUNCAO: (  \x1b[0mPOP )");
                return NULL;
                //return 0xffffffff; // -1 in a fancy way  if it was an integer function type
        }
        printf("\x1b[31mPOPED VALUE [%d]\x1b[0m\n", head->vals.val);

        node *ptr = head;  // *ptr = [0]
                head->next->size = head->size+1;  // [1].size += 1;
                head = head->next;  // [0] = [1]
                head->size--;  // Decrease the size by 1;
        free(ptr);

        fix_info(head);  // Fixing the id numbers.

        return head;
}

node *atPos(node *list, int index)
{
        if (index < 0 || index > list->size){
                fprintf(stderr, "OU O TAMANHO DA LISTA É MENOR DO QUE O INDICE, OU O INDEX EH UM VALOR NEGATIVO.\n\n");
                return NULL;
        }

        node *n = list;

        for(int i = 0; i < index; i++)
                n = n->next;

        return n;
}

int indexOf(node *list, int val)
{
        if (list == NULL){
                fprintf(stderr, "LIST WITHOUT ANYTHING INSIDE.\n\n");
                return -1;
        }

        node *n = list;
                while (n->vals.val != val && n->next != NULL)
                        n = n->next;

        if (n->vals.val == val)
                return n->id;
        else
                return -1;
}

bool isHead(node *list) {
        return (list->id == 0) ? true : false;
}

void rPlist(node *list)  // Recursive Print List
{
        if (list->next == NULL){   // Initial Recursive Test
                printf("ID: %d -----> Data: %d\n\n", list->id, list->vals.val);
                return;
        }

                printf("ID: %d -----> Data: %d\n", list->id, list->vals.val);  // Action on call
        rPlist(list->next);
}

void Print_list(node *list)
{
        putchar('\n');
        node *ptr = list;

        while (ptr->next){
                printf("ID: %d -----> Data: %d\n", ptr->id, ptr->vals.val);
                ptr = ptr->next;
        }
        printf("ID: %d -----> Data: %d\n\n", ptr->id, ptr->vals.val);  // The last one.
}
 // ---------------------------------------------------------------------------------------------->

void values_xchg(node *A, node *B){
        if (A && B)
        {
                int n = A->vals.val;
                A->vals.val = B->vals.val;
                B->vals.val = n;
        }
}

void val_set(node *head, int index, int val){
                if (index < 0 || index > head->size){
                        fprintf(stderr,"\x1b[31m[!!!] INDEX LESS THAN ZERO. OR the size is less than the index.\n\n");
                        return ;
                }
                node *n = head;

                while (n->id != index)
                        n = n->next;
 n->vals.val = val;
}


void Sort(node *head)   // Not working at all yet
{
        if (head == NULL){
                fprintf(stderr,"VOID NODE");
                return ;
        }
        unsigned short min[2] = {0,0};   // (val,Pos)
        int temp;

        while (head->next)
        {
          node *current = head;

          while (current->next){
                  if (current->vals.val < head->vals.val){
                      min[0] = current->vals.val;
                          min[1] = current->id;
                  }
                 current = current->next;
          }

          if (head->id > min[1])
          {
                  temp = head->vals.val;
                  head->vals.val = min[0];
                  val_set(head, min[1], temp);
          }

          head = head->next;
   }
}

node *create_node()
{
        node *new = (node*)malloc(sizeof(node));
                new->next = NULL;
                new->size = 0;
                new->id = 0;

                //new->vals = NULL;

        return new;
}


void main(void)
{
        node *list = create_node();
        Datanode algos = {42, 50.1, true};

        push(list, algos);

        srand(time(NULL));  // Loading the first pseudo-random seed
        algos.val = rand() % 76;

        push(list, algos);
        //list->push();

        Print_list(list);

                list = pop(list);  // Sempre fazer list = pop();
        rPlist(list);

                list = pop(list);

        srand(time(NULL)); // Loading the another pseudo-random seed.
        algos.val = rand() % 60;

        // ------------------------  RANDOM NUMBER GENERATED AGAIN ---------------------------------->-
                push(list, algos);

        puts("\n\n");

        for(int i = 0; i < 5; i++){
                algos.val = i*i;
                push(list, algos);
        }
        Print_list(list);
        puts("\x1b[33m------------------------------------------------------->\x1b[0m");

        for(int i = 1; i <= 5; i++)
                printf("\x1b[34mPOS: %d -----> %d\n\x1b[0m", i, atPos(list, i)->vals.val);

        printf("INDEXOF: %d\n", indexOf(list, 16));

        val_set(list, 1, 777);  // Done
        values_xchg(list, list->next->next);  // Done
        // Sort(list);  Not working yet at all

        fix_info(list);
        printf("SIZE-FIRST: %d | SIZE-SECOND: %d | SIZE-THIRD: %d\n", list->size, list->next->size, list->next->next->size);
        Print_list(list);
}
