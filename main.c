#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
  if (argc<5)
    {
      printf("Usage: ./city_manager --role <role> --user <name> <command>\n");
      return 1;
    }
  char role[20];
  char user[50];

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
    }
  printf("Role: %s\n", role);
  printf("User: %s\n", user);
  
  return 0;
}
