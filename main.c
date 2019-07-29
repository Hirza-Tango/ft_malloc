#include "ft_malloc.h"
#include <stdio.h>
#include <time.h>

int main()
{
	printf("Hi\n");
	void *small_stuff[ALLOC_NUM_TINY + 1];
	void *med_stuff[ALLOC_NUM_SMALL + 1];
	void *large_stuff[ALLOC_NUM_LARGE + 1];
	srand(time(NULL));
	for (int i = 0; i <= ALLOC_NUM_TINY; i++){
		small_stuff[i] = malloc(rand() % (ALLOC_SIZE_TINY - 1) + 1);
	}
	for (int i = 0; i <= ALLOC_NUM_SMALL; i++){
		med_stuff[i] = malloc(rand() % (ALLOC_SIZE_SMALL - ALLOC_SIZE_TINY - 1) + ALLOC_SIZE_TINY + 1);
	}
	for (int i = 0; i <= ALLOC_NUM_LARGE; i++){
		large_stuff[i] = malloc(rand() % (getpagesize() - ALLOC_SIZE_SMALL - 1) + ALLOC_SIZE_SMALL + 1);
	}
	show_alloc_mem();
	printf("These should be NULL: %p %p %p\n", small_stuff[ALLOC_NUM_TINY], med_stuff[ALLOC_NUM_SMALL], large_stuff[ALLOC_NUM_LARGE]);
	for (int i = 0; i <= ALLOC_NUM_TINY; i++){
		free(small_stuff[i]);
	}
	for (int i = 0; i <= ALLOC_NUM_SMALL; i++){
		free(med_stuff[i]);
	}
	for (int i = 0; i <= ALLOC_NUM_LARGE; i++){
		free(large_stuff[i]);
	}
	show_alloc_mem();
	small_stuff[0] = malloc(7);
	ft_memcpy(small_stuff[0], "abcder", 7);
	med_stuff[0] = malloc(10);
	ft_strcpy(med_stuff[0], "012345678");
	large_stuff[0] = malloc(2048);
	ft_strcpy(large_stuff[0], "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam laoreet lectus id sapien rhoncus pretium. Aliquam at vehicula ipsum, ut luctus quam. Maecenas tincidunt convallis viverra. Phasellus neque ante, facilisis eget urna vestibulum, aliquam posuere tellus. Suspendisse fermentum laoreet diam, a sodales est eleifend in. Fusce ultricies vestibulum augue, vitae malesuada orci tempor sed. Donec porta tincidunt dolor, sit amet dignissim erat fringilla ac. Nulla consectetur nec urna quis convallis. Fusce aliquam dignissim lectus quis fermentum. Nam porta ultrices ipsum non venenatis. Donec cursus tincidunt dapibus. Pellentesque gravida odio at urna varius, ut faucibus elit mattis. Sed ornare non odio sit amet varius. Cras quam nunc, feugiat ut mollis in, rutrum posuere sapien. Maecenas non dolor est. Nulla non luctus augue. Maecenas faucibus fringilla aliquam. Praesent euismod massa sit amet nisi molestie laoreet. Ut sit amet dolor magna. Vestibulum at sodales eros. Vivamus ac auctor dui. Suspendisse nec fermentum ligula. Nullam vel nunc nisl. Pellentesque consectetur risus sodales magna molestie, sed vulputate nulla dignissim. Curabitur augue ex, volutpat sit amet ultrices id, scelerisque a ipsum. Pellentesque tincidunt tellus eu lorem sodales maximus. Vestibulum risus arcu, consequat vulputate dolor pharetra, pellentesque tempor magna. Vestibulum risus massa, auctor id maximus commodo, auctor quis diam. Nulla hendrerit vulputate sapien. Fusce et laoreet ligula, eget tempor erat. Vestibulum tristique euismod nulla, ac auctor sem tempus vulputate. Sed varius purus quis sem pulvinar, eget consequat erat faucibus. Mauris sagittis, justo ac luctus rhoncus, libero leo tincidunt neque, sollicitudin vulputate dolor diam id justo. Curabitur finibus, nisl blandit accumsan mollis, est velit sollicitudin ipsum, in tempor purus nunc at lectus. Maecenas sit amet rutrum quam, at imperdiet sem. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nulla quis augue sagittis velit turpis du");
	show_alloc_mem();
	small_stuff[0] = realloc(small_stuff[0], 6);
	med_stuff[0] = realloc(med_stuff[0], 12);
	large_stuff[0] = realloc(large_stuff[0], 513);
	show_alloc_mem_ex();
	((char *)small_stuff[0])[5] = 0;
	((char *)med_stuff[0])[11] = 0;
	((char *)large_stuff[0])[512] = 0;
	ft_putendl("This should display 'abcde':");
	ft_putendl(small_stuff[0]);
	ft_putendl("This should display '012345678':");
	ft_putendl(med_stuff[0]);
	ft_putendl("This should end with '. Fusce aliq'");
	ft_putendl(large_stuff[0]);
	free(small_stuff[0]);
	free(med_stuff[0]);
	free(large_stuff[0]);
	show_alloc_mem_ex();
	ft_putendl("Bye");
}
