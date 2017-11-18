#include <unistd.h>

//reads the first sizeof() bytes into variables left to right
void get_flash(int sockfd, uint32_t *x, uint32_t *y){
	read(sockfd,x,sizeof(uint32_t)); //should read x from sockfd
	read(sockfd,y,sizeof(uint32_t));
}

void get_new(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y){
	read(sockfd,id,sizeof(uint32_t));
	read(sockfd,x,sizeof(uint32_t));
	read(sockfd,y,sizeof(uint32_t));

}

void get_delete(int sockfd, uint32_t *id){
	read(sockfd,id,sizeof(uint32_t));
}

void get_text(int sockfd, size_t len, char **str){
	read(sockfd,len,sizeof(size_t));
	read(sock,str,sizeof(&str));  //LIKELY TO FAIL

}

void get_move(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y){
	read(sockfd,id,sizeof(uint32_t));
	read(sockfd,x,sizeof(uint32_t));
	read(sockfd,y,sizeof(uint32_t));
}

void get_update(int sockfd, uint32_t *id, char *ch, uint8_t colour){
	read(sockfd,id,sizeof(uint32_t));
	read(sockfd,ch,sizeof(char));
	read(sockfd,colout,sizeof(uint8_t));

}

void get_health(int sockfd, uint8_t health){
	read(sockfd,health,sizeof(uint8_t));

}
