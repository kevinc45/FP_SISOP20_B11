#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#define NULL ( (void *) 0)

int dirlookup(int fd, int ino, char* p){
	struct dirent dir;
	while (read(fd, &dir, sizeof(dir)) == sizeof(dir)) {
		if (dir.inum == 0) continue;
		if (dir.inum == ino){
			memmove(p, dir.name, DIRSIZ);
			p[DIRSIZ] = '\0';
			return 1;
		}
	}
	return 0;
};

char* pathlookup(int ino, char* root, char* finpath){
	strcpy(root + strlen(root), "/" "..");
	struct stat st;
	stat(root, &st);
	
	if (st.ino == ino) return finpath;

	char* paths = NULL;
	int fd = open(root, 0);
	if (fd >= 0) {
		char* p = pathlookup(st.ino, root, finpath);
		if (p != NULL) {
			strcpy(p, "/");
			p += 1;
			if (dirlookup(fd, ino, p)) paths = p + strlen(p);
		}
		close(fd);
	}
	return paths;
};

int main() {
	char finpath[1000];
	char root[1000];
	struct stat st;
	
	finpath[0] = '\0';
	strcpy(root, ".");
	stat(root, &st);
	pathlookup(st.ino, root, finpath);
	if (finpath[0] == '\0') strcpy(finpath, "/");
	
	printf(1, "%s\n", finpath);
	exit();
}
