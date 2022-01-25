#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<jansson.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    char buffer[1024];
    fp=fopen("test.json",'r');
    fread(buffer,1024,1,fp);
    fclose(fp);

 
    json_t *root;
    json_error_t error;
    root=json_loads(buffer,0,&error);

    json_t* jtemp = NULL;
    char* myname = NULL;
    char* mycity = NULL;
    int myage;


    jtemp = json_object_get(root, "name");
    myname = (char*) json_string_value(jtemp);
    jtemp = json_object_get(root, "city");
    mycity = (char*) json_string_value(jtemp);
    jtemp = json_object_get(root, "age");
    myage = (int) json_integer_value(jtemp);

    printf("%s %s %d\n", myname, mycity, myage);
}