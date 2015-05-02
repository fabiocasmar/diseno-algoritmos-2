#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>      
#include <stack>          
#include <vector>         
#include <deque>   
using namespace std;

#define  MAX_LINE_LENGTH 999 

int main( int argc, char **argv )
{
    char str[ MAX_LINE_LENGTH +1 ] ;
    ssize_t nchars; 
    stack <iter > pila; 
    state_t state; 
    state_t child;
    ruleid_iterator_t iter; 
    int ruleid ; 
    int childCount;


    printf("Please enter a state followed by ENTER: ");
    if ( fgets(str, sizeof str, stdin) == NULL ) {
		printf("Error: empty input line.\n");
		return 0; 
    }

    nchars = read_state(str, &state);
    if (nchars <= 0) {
		printf("Error: invalid state entered.\n");
		return 0; 
    }

    childCount = 0;
	init_fwd_iter(&iter, &state);
	while((ruleid = next_ruleid(&iter)) >= 0){
		apply_fwd_rule( ruleid, &state, &child );
		++childCount;
	} 

    return 0;
}