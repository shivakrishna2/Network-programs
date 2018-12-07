#include<stdio.h>
#include <string.h>
#include<stdint.h>

#define ADDRLEN 16


uint8_t printIPRangeUtil(uint32_t  net_ip, uint32_t net_mask);

// To convert IPV4 binary to String
char* ConvertIPv4B2S(uint32_t ip_addr, char *ip_addr_str)
{
    unsigned char *ip;

    ip = (unsigned char *)&ip_addr;
    sprintf(ip_addr_str, "%d.%d.%d.%d", ip[3] & 0xff, ip[2] & 0xff, ip[1] & 0xff, ip[0] & 0xff);
    return ip_addr_str;

}

// To convert IPV4 string to binary
uint8_t ConvertIPv4S2B(char *ip4_addr_str, uint32_t *net_ip)
{
    uint32_t    ip[4];
    uint8_t     i;
    uint8_t     ret;

    if(ip4_addr_str == NULL)
    {
        return 0;
    }

    sscanf(ip4_addr_str,"%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

    for(i = 0; i < 4; i++)
    {
        if(ip[i] > 255)
        {
            return 0;
        }
    }

    *net_ip = (ip[0] << 24) +(ip[1] << 16) +(ip[2] << 8) + ip[3];

    return 1;

}

uint8_t printIPRange(char *sub_str)
{
    uint32_t net_ip = 0;
    uint32_t  net_mask = 0;
    uint32_t prefix = 0;
    char *net_ip_str;
    char *prefix_str;
    char *token;
    char *save_ptr = NULL;
    char delim[] = "/";

    int i = 0;
    uint8_t left_bits = 0;
    uint8_t ret = 0;
    if(sub_str == NULL)
        return 0;

    token = strtok(sub_str, delim);
    while( token != NULL )
    {
        if (i == 0)
        {
            net_ip_str = token;
        }

        if (i == 1)
        {
           prefix_str = token;
           prefix = atoi(prefix_str);
        }

        if (i > 1)
             return 0;

        token = strtok(NULL, delim);
        i++;
    }

    ret = ConvertIPv4S2B(net_ip_str, &net_ip);

    if(! ret)
        return 0;

    if (prefix > 32)
        return 0;

    left_bits = 32 - prefix;

    net_mask = (0xffffffff << left_bits) & 0xffffffff;
    printIPRangeUtil(net_ip, net_mask);
}


uint8_t printIPRangeUtil(uint32_t  net_ip, uint32_t net_mask)
{

    char ip_str[ADDRLEN];
    char first_ip_str[ADDRLEN];
    char  last_ip_str[ADDRLEN];
    char net_ip_str[ADDRLEN];
    char net_mask_str[ADDRLEN]; 
    uint32_t i;
    uint32_t first_ip;
    uint32_t last_ip;
    uint32_t ip;

    first_ip = net_ip & net_mask;
    last_ip = net_ip | ~net_mask;


    printf(" Network IP : %s\n Network Mask : %s\n Firts ip : %s\n Last_ip %s\n", ConvertIPv4B2S(net_ip, net_ip_str), ConvertIPv4B2S(net_mask, net_mask_str), ConvertIPv4B2S(first_ip, first_ip_str), ConvertIPv4B2S(last_ip,last_ip_str));

    // To Print all IP's in range first_ip and last_ip, Uncomment Below loop
    /*
    for ( ip = first_ip; ip <= last_ip; ++ip) {
        ConvertIPv4BinaryToStr(ip, ip_str);
        printf("%s\n", ip_str);
    } */
}

int main()
{
    char sub_str[100] = "10.0.0.1/22";
    printIPRange(sub_str);

    return 0;
}

