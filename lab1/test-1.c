
#include <stdio.h>
#include <ctype.h>
#define STRSIZ 100

//Recursive Function to Extract Capital Letters from a String
//Forms a string containing all the capital letters found in the input parameter str.
// caps has sufficient space to store all caps in str plus the null
char*
find_caps (char caps[],      //output - string of all caps found in str
          const char str[]) //input - string from which to extract caps
{
      char restcaps[STRSIZ]; //caps from reststr (rest of string)

      if (str[0] == '\0')
            caps[0] = '\0'; //no letters in str means no caps in str
      else
            if (isupper(str[0]))
                  sprintf(caps, "%c%s", str[0], find_caps(restcaps, &str[1]));
            else
                  find_caps(caps, &str[1]);

      return (caps);
}

int
main (void) {
    char sentence [] = "This is just a Test for Assignment-1";
    char capital_letters[STRSIZ];
    find_caps (capital_letters, sentence);
    
    printf ("%s\n", capital_letters);
    return (0);
    
}