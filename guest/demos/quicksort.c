/**
 * Quick sort concolic execution demo.
 * Code taken from http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Quicksort#C
 */

#include <s2e.h>

void swap(int *a, int *b)
{
  int t=*a; *a=*b; *b=t;
}
void sort(int arr[], int beg, int end)
{
  if (end > beg + 1)
  {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r)
    {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l);
    sort(arr, r, end);
  }
}


int main(void)
{
  int num_list[]={5,4,3,2,1};

  s2e_enable_forking();
  s2e_make_concolic(&num_list, sizeof(num_list), "array");

  int len=sizeof(num_list)/sizeof(num_list[0]);
  char *sep="";
  int i;
  sort(num_list,0, len);

  printf("sorted_num_list={");
  for(i=0; i<len; i++){
    printf("%s%d",sep,num_list[i]);
    sep=", ";
  }
  printf("};\n");

  s2e_kill_state(0, "Sort completed");

  return 0;
}