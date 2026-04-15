#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

void create_district()
{
  
}

int main(int argc, char *argv[])
{
  if (argc<5)
    {
      printf("Usage: ./city_manager --role <role> --user <name> <command>\n");
      return 1;
    }
  char role[20];
  char user[50];
  char district[50];

  for(int i=1;i<argc;i++)
    {
      if (strcmp(argv[i], "--role") == 0)
	{
	  strcpy(role,argv[i+1]);
	}
         if (strcmp(argv[i], "--user") == 0)
	{
	  strcpy(user,argv[i+1]);
	}
	   if (strcmp(argv[i], "--add") == 0)
	{
	  strcpy(district,argv[i+1]);
	}
    }
  if (strcmp(role, "manager") !=0)
    {
      printf("not manager\n");
      return 1;
    }
  printf("Role: %s\n", role);
  printf("User: %s\n", user);
  create_district(district);
  return 0;
}
