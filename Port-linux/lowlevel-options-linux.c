#include <stdio.h>
#include "sys/stat.h"
#include "Portable.h"

/*
 * results 0 - ok
          -1 - unable to open temp. file
          -2 - unable to open resolv.conf file
 */
int dns_add(const char * ifname, int ifaceid, const char * addrPlain) {
    FILE * f;
    if ( !(f=fopen(RESOLVCONF_FILE,"a+"))) {
	return -1;
    }

    fprintf(f,"nameserver %s\n",addrPlain);
    fclose(f);
    return 0;
}

int dns_del(const char * ifname, int ifaceid, const char *addrPlain) {
    FILE * f, *f2;
    char buf[512];
    int found=0;
    char * s;

    unlink(RESOLVCONF_FILE".old");
    rename(RESOLVCONF_FILE,RESOLVCONF_FILE".old");
    f = fopen(RESOLVCONF_FILE".old","r");
    f2 = fopen(RESOLVCONF_FILE,"w"); 
    while (fgets(buf,511,f)) {
	if ( (!found) && (strstr(buf, addrPlain)) ) {
	    found = 1;
	    continue;
	}
	fprintf(f2,"%s",buf);
    }
    fclose(f);
    fclose(f2);

    chmod(RESOLVCONF_FILE,12);
    return 0;
}

int domain_add(const char* ifname, int ifaceid, const char* domain) {
    FILE * f;
    char buf[512];
    memset(buf,0,512);
    if ( !(f=fopen(RESOLVCONF_FILE,"a+"))) {
	return -1;
    }
    fprintf(f,"search %s\n",domain);
    fclose(f);
    if (!(f=fopen(WORKDIR"/tmp-domain","a+"))) {
	return -2;
    }
    fprintf(f,"%s\n",domain);
    fclose(f);
    return 0;
}

int domain_del(const char * ifname, int ifaceid, const char *domain) {
    FILE * f, *f2;
    char buf[512];
    int found=0;

    unlink(RESOLVCONF_FILE".old");
    rename(RESOLVCONF_FILE,RESOLVCONF_FILE".old");
    if ( !(f = fopen(RESOLVCONF_FILE".old","r")) )
	return -1;
    if ( !(f2= fopen(RESOLVCONF_FILE,"w+")))
	return -1;
    while (fgets(buf,511,f)) {
	if ( (!found) && (strstr(buf, domain)) ) {
	    found = 1;
	    continue;
	}
	fprintf(f2,"%s",buf);
    }
    fclose(f);
    fclose(f2);

    chmod(RESOLVCONF_FILE,12);
    return 0;
}

int ntp_add(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int ntp_del(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int timezone_set(const char* ifname, int ifindex, const char* timezone){
    return 0;
}

int timezone_del(const char* ifname, int ifindex, const char* timezone){
    return 0;
}

int sipserver_add(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int sipserver_del(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int sipdomain_add(const char* ifname, int ifindex, const char* domain){
    return 0;
}

int sipdomain_del(const char* ifname, int ifindex, const char* domain){
    return 0;
}

int nisserver_add(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int nisserver_del(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int nisdomain_set(const char* ifname, int ifindex, const char* domain){
    return 0;
}

int nisdomain_del(const char* ifname, int ifindex, const char* domain){
    return 0;
}

int nisplusserver_add(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int nisplusserver_del(const char* ifname, const int ifindex, const char* addrPlain){
    return 0;
}

int nisplusdomain_set(const char* ifname, int ifindex, const char* domain){
    return 0;
}

int nisplusdomain_del(const char* ifname, int ifindex, const char* domain){
    return 0;
}
