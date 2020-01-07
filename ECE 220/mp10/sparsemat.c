/* We implement seven fucntions to add, multiply, set and load a matrix. Functions use each other to set uo the right zero matrix.
   Partners: rkadiri2, yab2, heshama2 */

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>



static sp_tuples_node * pcut;


sp_tuples * load_tuples(char* input_file)
{
  FILE * file;
  sp_tuples *t;
  int rows, cols ;


  t = (sp_tuples *)malloc(sizeof(sp_tuples));
  file = fopen(input_file, "r");
    if (file==NULL) {
      printf("invaled file %s\n", input_file);
      return NULL;
    }
    fscanf(file,"%d %d",&rows, &cols);

    int m,n;
    double v;
    long long int i;
    t->m=rows;
    t->n=cols;

    t->nz=0;
    for (i = 0; i < rows*cols; i++) {
      if(fscanf(file,"%d %d %lf",&m, &n, &v)==3){
        set_tuples(t, m, n, v);//new
      }
      else
        break;
    }


    fclose(file);

    return t;
}


double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  sp_tuples_node * t;
  int i,cnt;
  cnt= mat_t->nz;
  t = mat_t->tuples_head;
  //if(t->row==-1)
    //return 0;
  for (i = 0; i < cnt; i++) {
    if(row==t->row && col==t->col){
      pcut=t;
      return t->value;
    }

    else{
      t=t->next;
    }
  }

    return 0;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  int i,count;
  sp_tuples_node **f, *tmp, *t;

  count= mat_t->nz;
  f = &mat_t->tuples_head;
  t = *f;
  if(value==0 && gv_tuples(mat_t, row, col)==0)
    return;
  else if(value==0){
    for (i = 0; i < count; i++) {
      if(row== t->row && col==t->col){
        t->value=0;
        tmp=t;
        t= t->next;
        *f=t;
        free(tmp);
        count--;
        mat_t->nz=count;
        return;
      }
      f=&t->next;
      t=*f;
    }
  }
  else if(count==0){
    t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    t->row=row;
    t->col=col;
    t->value=value;
    t->next=NULL;
    *f=t;
    count++;
    mat_t->nz=count;      // Update nz
    return;


  }
  else if(gv_tuples(mat_t, row, col)!=0){
    pcut->value=value;

  }
  else if(t->row>row||(t->row==row&&t->col>col)){
    tmp=t;
    t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    t->row=row;
    t->col=col;
    t->value=value;
    t->next=tmp;
    *f=t;
    count++;
    mat_t->nz=count;
    return;
  }

  else{
    for (i = 0; i < count; i++){
      if(t->row>row){
          tmp=t;
          t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
          t->row=row;
          t->col=col;
          t->value=value;
          t->next=tmp;
          *f=t;
          count++;
          mat_t->nz=count;
          return;

      }
      else if(t->row==row){
        if(t->col<col){
          if(t->next!=NULL){
            f=&t->next;
            t=*f;
            continue;
          }

        }
        else{
          tmp=t;
          t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
          t->row=row;
          t->col=col;
          t->value=value;
          t->next=tmp;
          *f=t;
          count++;
          mat_t->nz=count;
          return;


        }
      }

      if(t->next==NULL)
        break;

      f=&t->next;
      t=*f;


    }
    tmp=t;
    t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    t->row=row;
    t->col=col;
    t->value=value;
    t->next=NULL;
    tmp->next=t;
    count++;
    mat_t->nz=count;
    return;
    return;
    t=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    t->row=row;
    t->col=col;
    t->value=value;
    t->next=NULL;
    *f=t;
    count++;
    mat_t->nz=count;
    return;
  }


  return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)         // Writes sparse matrix data to text file
{
  FILE *file;
  file = fopen(file_name, "w");
  if (file==NULL) {
    printf("invaled file %s\n", file_name);
    return;
  }
  sp_tuples_node * t;
  int rows, cols,i,count;
  //double v;
  rows = mat_t->m;
  cols= mat_t->n;
  count= mat_t->nz;
  t = mat_t->tuples_head;
  fprintf(file, "%d %d\n",rows, cols );
  for (i = 0; i < count; i++) {
    fprintf(file, "%d %d %lf\n",t->row, t->col, t->value );
    t= t->next;
  }
  fclose(file);

	return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

  long int countA, countB, rows, cols, i;
  sp_tuples_node * t1, *t2;
  sp_tuples *t=NULL;
  rows= matA->m;
  cols= matA->n;
  if(rows!=matB->m || cols!= matB->n)
    return NULL;
  countA=matA->nz;
  t1= matA->tuples_head;
  t2= matB->tuples_head;
  countB=matB->nz;
  t = (sp_tuples *)malloc(sizeof(sp_tuples));
  t->nz=0;
  t->m=rows;
  t->n=cols;
  for (i = 0; i < countA; i++) {
    set_tuples(t, t1->row, t1->col, t1->value);
    t1=t1->next;

  }
  for (i = 0; i < countB; i++) {
    if(gv_tuples(t,t2->row,t2->col)){
      pcut->value+=t2->value;
      t2=t2->next;
    }
    else{
    set_tuples(t, t2->row, t2->col, t2->value);
    t2=t2->next;
  }

  }

  return t;

}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  long int countA, countB, rows, cols, i, j,col, rowsA, colsB;
  double v;
  sp_tuples_node * t1, *t2, *tmp;
  sp_tuples *t=NULL;
  rows= matB->m;
  cols= matA->n;
  colsB=matB->n;
  rowsA=matA->m;
  if(rows!=cols)
    return NULL;
  countA=matA->nz;
  t1= matA->tuples_head;
  t2= matB->tuples_head;
  countB=matB->nz;
  t = (sp_tuples *)malloc(sizeof(sp_tuples));
  t->nz=0;
  t->m=rowsA;
  t->n=colsB;
  tmp = t2;
  for (i = 0; i < countA; i++) {
    col=t1->col;
    t2= tmp;

    for (j = 0; j < countB; j++) {
      if (col==t2->row) {
        v=gv_tuples(t, t1->row, t2->col)+((t1->value) * (t2->value));
        set_tuples(t,t1->row, t2->col, v);
        t2=t2->next;
        continue;
      }
      else if(col<t2->row){
        break;
      }
      t2=t2->next;
    }

    t1=t1->next;

  }
  return t;

}

void destroy_tuples(sp_tuples * mat_t){           // All memory addresses are freed 

  sp_tuples_node* t, *tmp;//, *tmp2;
  long int i;
  int nz;
  nz=mat_t->nz;
  t= mat_t->tuples_head;
  for (i = 0; i < nz; i++) {
    if(t!=NULL){
      tmp=t;
      t=t->next;
      free(tmp);

    }

    }

    return;
}
