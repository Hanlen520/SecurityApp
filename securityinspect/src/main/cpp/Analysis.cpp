//
// Created by qtfreet00 on 2018/1/22.
//

#include "Analysis.h"
#include "Util.h"

void findInMaps(int pid, const char *filter, vector<string> &result) {
    char data[256];
    char s[64] = {0};
    sprintf(s, "/proc/%d/maps", pid);
    FILE *fd = fopen(s, "r");
    if (fd == NULL) {
        return;
    }
    char path[128] = {0};
    char uid[10] = {0};
    while (fgets(data, 256, fd)) {
        int len = (int) strlen(data);
        if (len <= 0) {
            continue;
        }
        data[--len] = '\0';
        if (sscanf(data, "%*llx-%*llx %s %*s %*s %*s %s", uid, path) != 2) {
            continue;
        }
        if (strcmp(uid, "r-xp") == 0 && endsWith(path, filter)) {
            result.push_back(path);
        }
    }
    fclose(fd);
}


int countPathFromUid() {
    int counts = 0;
    int pid = _getpid();
    unsigned int uid = _getuid();
    struct passwd *password = getpwuid(uid);
    if (password == NULL) {
        return counts;
    }
    char *user = password->pw_name;
    char sh[64] = {0};
    sprintf(sh, "ps |grep %s", user);
    FILE *fp = popen(sh, "rb");
    if (!fp) {
        return counts;
    }
    char data[256] = {0};
    int fake_pid = 0;
    char pkg[128] = {0};
    while (fgets(data, 256, fp)) {
        if (sscanf(data, "%*s    %d  %*d  %*s %*s %*s %*s %*s %s", &fake_pid, pkg) != 2) {
            continue;
        }
        if (fake_pid != pid) {
            char path[128] = {0};
            sprintf(path, "/data/data/%s", pkg);
            if (strcmp(path, "/data/data/") != 0) {
                if (access(path, F_OK) == 0) {
                    counts++;
                }
            }
        }
    }
    pclose(fp);
    return counts;
}