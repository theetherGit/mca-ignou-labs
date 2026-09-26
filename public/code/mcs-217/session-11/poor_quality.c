#include <stdio.h>
int t,u;
int main(){int n,i,a[100],s=0,h=0;float v;
printf("Enter number of students: ");scanf("%d",&n);
	for(i=0;i<n;i++){printf("Marks of student %d: ",i+1);scanf("%d",&a[i]);}
  for(i=0;i<n;i++)s=s+a[i];
v=(float)s/n;
	for(i=0;i<n;i++)if(a[i]>h)h=a[i];
  printf("Average marks: %.2f\n",v);printf("Highest marks: %d\n",h);
for(i=0;i<n;i++){
if(a[i]>=90)printf("Student %d: %d -> A\n",i+1,a[i]);
    else if(a[i]>=75)printf("Student %d: %d -> B\n",i+1,a[i]);
else if(a[i]>=60)printf("Student %d: %d -> C\n",i+1,a[i]);
	else if(a[i]>=40)printf("Student %d: %d -> D\n",i+1,a[i]);
  else printf("Student %d: %d -> F\n",i+1,a[i]);}
if(v>=90)printf("Class average grade: A\n");
else if(v>=75)printf("Class average grade: B\n");
	else if(v>=60)printf("Class average grade: C\n");
  else if(v>=40)printf("Class average grade: D\n");
else printf("Class average grade: F\n");
return 0;}
