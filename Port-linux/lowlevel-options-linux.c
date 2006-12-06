/*                                                                           
 * Dibbler - a portable DHCPv6                                               
 *                                                                           
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>                           
 *          Marek Senderski <msend@o2.pl>                                    
 *                                                                           
 * released under GNU GPL v2 or later licence                                
 *                                                                           
 * $Id: lowlevel-options-linux.c,v 1.4 2006-12-06 00:19:06 thomson Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2004-11-30 00:54:25  thomson
 * Minor improvements.
 *
 *
 */

#include <stdio.h>
#include "sys/stat.h"
#include "Portable.h"

#define CR 0x0a
#define LF 0x0d

extern char * Message;

/*
 * results 0 - ok
          -1 - unable to open temp. file
          -2 - unable to open resolv.conf file
 */
int dns_add(const char * ifname, int ifaceid, const char * addrPlain) {
    FILE * f;
    unsigned char c;
    if ( !(f=fopen(RESOLVCONF_FILE,"a+"))) {
	return -1;
    }

    fseek(f, -1, SEEK_END);
    c = fgetc(f);
    fseek(f,0, SEEK_END);
    if ( (c!=CR) && (c!=LF) ) {
	fprintf(f,"\n");
    }

    fprintf(f,"nameserver %s\n",addrPlain);
    fclose(f);
    return 0;
}

int dns_del(const char * ifname, int ifaceid, const char *addrPlain) {
    FILE * f, *f2;
    char buf[512];
    int found=0;
    struct stat st;
    memset(&st,0,sizeof(st));
    stat(RESOLVCONF_FILE, &st);

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

    chmod(RESOLVCONF_FILE, st.st_mode);
    return 0;
}

int domain_add(const char* ifname, int ifaceid, const char* domain) {
    FILE * f;
    unsigned char c;
    if ( !(f=fopen(RESOLVCONF_FILE,"a+"))) {
	return -1;
    }

    fseek(f, -1, SEEK_END);
    c = fgetc(f);
    fseek(f,0, SEEK_END);
    if ( (c!=CR) && (c!=LF) ) {
	fprintf(f,"\n");
    }

    fprintf(f,"search %s\n",domain);
    fclose(f);

    return 0;
}

int domain_del(const char * ifname, int ifaceid, const char *domain) {
    FILE * f, *f2;
    char buf[512];
    int found=0;
    struct stat st;
    memset(&st,0,sizeof(st));
    stat(RESOLVCONF_FILE, &st);

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

    chmod(RESOLVCONF_FILE,st.st_mode);
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

int prefix_add(const char* ifname, int ifindex, const char* prefixPlain, int prefixLength) {

    FILE * f = fopen(RADVD_FILE, "w+");
    if (!f) {
	sprintf(Message, "Unable to open %s file.", RADVD_FILE);
	return LOWLEVEL_ERROR_FILE;
    }
    
    fprintf(f, "# Router Advertisement config file generated by Dibbler \n");
    fprintf(f, "interface %s \n", ifname);
    fprintf(f, "{ \n");
    fprintf(f, "     AdvSendAdvert on; \n");
    fprintf(f, "     prefix %s/%d", prefixPlain, prefixLength);
    fprintf(f, "     { \n");
    fprintf(f, "         AdvOnLink on;\n");
    fprintf(f, "         AdvAutonomous false;\n");
    fprintf(f, "     };\n");
    fprintf(f, "};\n");

    fclose(f);

    return 0;
}

int prefix_del(const char* ifname, int ifindex, const char* prefixPlain, int prefixLength) {
    return 0;
}
