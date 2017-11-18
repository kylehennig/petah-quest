#include <unistd.h>


void get_flash(int sockfd, uint32_t *x, uint32_t *y){
	read(sockfd,x,sizeof(x)); //should read x from sockfd
	read(sockfd,x,sizeof(y));
}

void get_new(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y){}
void get_delete(int sockfd, uint32_t *id){}
void get_text(int sockfd, size_t len, char **str){}
void get_move(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y){}
void get_update(int sockfd, uint32_t *id, char *ch, uint8_t colour){}
void get_health(int sockfd, uint8_t health){}
