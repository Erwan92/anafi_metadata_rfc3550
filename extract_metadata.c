#include<pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<pthread.h>
#include<glib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include "struct_rtp.h"
#include "struct_anafi_metadata.h"

pcap_if_t *devs;
pcap_t *p;
char *devname;
static char errbuf[PCAP_ERRBUF_SIZE];
static float grd,nsp,esp,dsp,asp,dqw,dqx,dqy,dqz,fbw,fbx,fby,fbz,fvw,fvx,fvy,fvz,fet,fig,rgg,bgg,goodput;
static uint8_t gps,qual,rssi,bat,state,mode;
static float cap,angle_cam,spd,lat_vise,lon_vise,dist_vise;
static float lat,lon,alt,hfov,vfov;

float calc_speed(float nsp, float esp){
	spd = sqrt(pow(nsp, 2)+ pow(esp, 2));
	return spd;
}

void extract_rfc3550(const u_char *Buffer , int Size)
{
	unsigned short iphdrlen;
	unsigned short udphdrlen;
	struct ethhdr *eth = (struct ethhdr *)Buffer;
	struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
	iphdrlen = iph->ihl*4;
	struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
	udphdrlen = sizeof udph;
	struct rtphdr *rtph = (struct rtphdr*)(Buffer + udphdrlen + iphdrlen  + sizeof(struct ethhdr));
	struct metadata *meta = (struct metadata*)(Buffer + sizeof(struct rtphdr) + udphdrlen + iphdrlen  + sizeof(struct ethhdr));	

	if(rtphdr->X == 1){	//Buffer[42] == 144
	grd = ntohl(meta->ground_distance)/pow(2,16);
	lat = ntohl(meta->latitude)/pow(2,22);
	lon = ntohl(meta->longitude)/pow(2,22);
	alt = ntohs(meta->alt1)+(meta->alt2/pow(2,8));
	gps = meta->sv;
	nsp = ntohs(meta->north_speed)/pow(2,8);
	esp = ntohs(meta->east_speed)/pow(2,8);
	dsp = ntohs(meta->down_speed)/pow(2,8);
	asp = (int16_t)ntohs(meta->air)/pow(2,8);
	dqw = ((int16_t)ntohs(meta->drone_w))/pow(2,14);
	dqx = ((int16_t)ntohs(meta->drone_x))/pow(2,14);
	dqy = ((int16_t)ntohs(meta->drone_y))/pow(2,14);
	dqz = ((int16_t)ntohs(meta->drone_z))/pow(2,14);
	fbw = (int16_t)ntohs(meta->frame_base_w)/pow(2,14);
	fbx = (int16_t)ntohs(meta->frame_base_x)/pow(2,14);
	fby = (int16_t)ntohs(meta->frame_base_y)/pow(2,14);
	fbz = (int16_t)ntohs(meta->frame_base_z)/pow(2,14);
	fvw = (int16_t)ntohs(meta->frame_w)/pow(2,14);
	fvx = (int16_t)ntohs(meta->frame_x)/pow(2,14);
	fvy = (int16_t)ntohs(meta->frame_y)/pow(2,14);
	fvz = (int16_t)ntohs(meta->frame_z)/pow(2,14);
	fet = (uint16_t)ntohs(meta->exposure_time)/pow(2,8);
	fig = (uint16_t)ntohs(meta->gain);
	rgg = (uint16_t)ntohs(meta->awb_r_gain)/pow(2,14);
	bgg = (uint16_t)ntohs(meta->awb_b_gain)/pow(2,14);
	hfov = (uint16_t)ntohs(meta->picture_hfov)/pow(2,8);
	vfov = (uint16_t)ntohs(meta->picture_vfov)/pow(2,8);
	goodput = (uint16_t)ntohs(meta->goodput1)*256+(uint8_t)meta->goodput2;
	qual = (uint8_t)meta->link_quality;
	rssi = (int8_t)meta->wifi_rssi;
	bat = (uint8_t)meta->battery;
	state = (uint8_t)meta->state;
	mode = (uint8_t)meta->mode;
	cap = -180-atan2(2*(dqw*dqz+dqx*dqy), 1-2*(dqy*dqy+dqz*dqz))*180/M_PI;
	angle_cam = 90+((-M_PI/2)+ 2*atan2(sqrt(1+2*(fvw*fvy-fvx*fvz)),sqrt(1-2*(fvw*fvy-fvx*fvz))))*180/M_PI;
	spd = calc_speed(nsp, esp);
	printf("CAP : %f - angle camera : %f\n",cap,angle_cam);
	printf("Ground distance : %f\n",ntohl(meta->ground_distance)/pow(2,16));
	printf("Latitude : %f\n",ntohl(meta->latitude)/pow(2,22));
	printf("Longitude : %f\n",ntohl(meta->longitude)/pow(2,22));
	printf("Altitude : %f\n",ntohs(meta->alt1)+(meta->alt2/pow(2,8)));
	printf("GPS SV : %d\n",meta->sv);
	printf("North speed : %f\n",ntohs(meta->north_speed)/pow(2,8));
	printf("East speed : %f\n",ntohs(meta->east_speed)/pow(2,8));
	printf("Down speed : %f\n",ntohs(meta->down_speed)/pow(2,8));
	printf("Air speed : %f\n",(int16_t)ntohs(meta->air)/pow(2,8));
	printf("Quaternion W : %f\n",((int16_t)ntohs(meta->drone_w))/pow(2,14));
	printf("Quaternion X : %f\n",((int16_t)ntohs(meta->drone_x))/pow(2,14));
	printf("Quaternion Y : %f\n",((int16_t)ntohs(meta->drone_y))/pow(2,14));
	printf("Quaternion Z : %f\n",((int16_t)ntohs(meta->drone_z))/pow(2,14));
	printf("Frame base view W : %f\n",(int16_t)ntohs(meta->frame_base_w)/pow(2,14));
	printf("Frame base view X : %f\n",(int16_t)ntohs(meta->frame_base_x)/pow(2,14));
	printf("Frame base view Y : %f\n",(int16_t)ntohs(meta->frame_base_y)/pow(2,14));
	printf("Frame base view Z : %f\n",(int16_t)ntohs(meta->frame_base_z)/pow(2,14));
	printf("Frame view W : %f\n",(int16_t)ntohs(meta->frame_w)/pow(2,14)); 
	printf("Frame view X : %f\n",(int16_t)ntohs(meta->frame_x)/pow(2,14));
	printf("Frame view Y : %f\n",(int16_t)ntohs(meta->frame_y)/pow(2,14));
	printf("Frame view Z : %f\n",(int16_t)ntohs(meta->frame_z)/pow(2,14));
	printf("Frame exposure time : %f\n",(uint16_t)ntohs(meta->exposure_time)/pow(2,8));
	printf("Frame ISO gain : %d\n",(uint16_t)ntohs(meta->gain));
	printf("White balance R/G gain : %f\n",(uint16_t)ntohs(meta->awb_r_gain)/pow(2,14));
	printf("White balance B/G gain : %f\n",(uint16_t)ntohs(meta->awb_b_gain)/pow(2,14));
	printf("Picture horizontal FOV : %f\n",(uint16_t)ntohs(meta->picture_hfov)/pow(2,8));
	printf("Picture vertical FOV : %f\n",(uint16_t)ntohs(meta->picture_vfov)/pow(2,8));
	printf("Link goodput : %d\n",(uint16_t)ntohs(meta->goodput1)*256+(uint8_t)meta->goodput2);
	printf("Link quality : %d\n",(uint8_t)meta->link_quality);
	printf("Wifi RSSI : %d\n",(int8_t)meta->wifi_rssi);
	printf("Batterie : %d\n",(uint8_t)meta->battery);
	printf("State : %d\n",(uint8_t)meta->state);
	printf("Mode : %d\n",(uint8_t)meta->mode);
	//4531
	printf("Frame timestamp (µs, monotonic), high 32 bits : %d\n",(uint32_t)ntohl(meta->frame_timestamp_h));
	printf("Frame timestamp (µs, monotonic), low 32 bits : %d\n",(uint32_t)ntohl(meta->frame_timestamp_l));
	//4533
	printf("Framing target latitude : %f\n",(int32_t)ntohl(meta->framing_target_latitude)/pow(2,22));
	printf("Framing target longitude : %f\n",(int32_t)ntohl(meta->framing_target_longitude)/pow(2,22));
	printf("Framing target altitude ASL : %f\n",(int32_t)ntohl(meta->framing_target_altitude)/pow(2,16));
	printf("Flight destination latitude : %f\n",(int32_t)ntohl(meta->flight_destination_latitude)/pow(2,22));
	printf("Flight destination longitude : %f\n",(int32_t)ntohl(meta->flight_destination_longitude)/pow(2,22));
	printf("Flight destination altitude ASL : %f\n",(int32_t)ntohl(meta->flight_destination_altitude)/pow(2,16));
	printf("Automation animation : %d\n",(uint8_t)meta->automation_animation);
	printf("Follow me enabled : %d\n",meta->follow_me_bool);
	printf("Look at me enabled : %d\n",meta->look_at_me_bool);
	printf("Angle locked: %d\n",meta->angle_locked_bool);
	//4534
	printf("Minimum temperature spot x-coordinate (relative to frame width) : %f\n",(int16_t)ntohs(meta->min_x)/pow(2,5));
	printf("Minimum temperature spot y-coordinate (relative to frame height) : %f\n",(int16_t)ntohs(meta->min_y)/pow(2,5));
	printf("Minimum temperature spot temperature value (K) : %f\n",(int16_t)ntohs(meta->min_temp)/pow(2,5));
	printf("Maximum temperature spot x-coordinate (relative to frame width) : %f\n",(int16_t)ntohs(meta->max_x)/pow(2,5));
	printf("Maximum temperature spot y-coordinate (relative to frame height) : %f\n",(int16_t)ntohs(meta->max_y)/pow(2,5));
	printf("Maximum temperature spot temperature value (K): %f\n",(int16_t)ntohs(meta->max_temp)/pow(2,5));
	printf("Probe temperature x-coordinate (relative to frame width) : %f\n",(int16_t)ntohs(meta->probe_x)/pow(2,5));
	printf("Probe temperature y-coordinate (relative to frame height) : %f\n",(int16_t)ntohs(meta->probe_y)/pow(2,5));
	printf("Probe temperature temperature value (K) : %f\n",(int16_t)ntohs(meta->probe_temp)/pow(2,5));
	printf("Calibration state : %d\n",(uint8_t)meta->calib_state);
	//4536
	printf("Champ inconnu 1 : %f\n",ntohl(meta->champ_inconnu)/pow(2,22));
	printf("Champ inconnu 2 : %f\n",ntohl(meta->champ_inconnu2)/pow(2,22));
	printf("Champ inconnu 3 : %f\n",ntohl(meta->champ_inconnu3)/pow(2,22));
	}
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
	int size = header->len;
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	if(iph->protocol == 17){
		extract_rfc3550(buffer , size);
	}
}

int sniff(char *devname, char *arg){
pcap_t *handle;
printf("Ouverture carte %s pour sniffing ... " , devname);
handle = pcap_open_live(devname , 65536 , 1 , 0 , errbuf);
	if (handle == NULL) 
	{
		printf(stdout, "Impossible d'ouvrir la carte %s : %s\n" , devname , errbuf);
		exit(1);
	}
	printf("Carte ouverte avec succes\n");
	pcap_loop(handle , -1 , process_packet , arg);
	return 0;
}

int main(int argc, char *argv[]){
	sniff("enp0s31f6", drone);
	pcap_freealldevs(devs);
	return 1;
}
