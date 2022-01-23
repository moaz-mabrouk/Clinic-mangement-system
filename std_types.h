/*----------------------char--------------------------*/
typedef char signed 				 s8; 
typedef char unsigned 			 	 u8; 

/*-------------------short int-----------------------*/
typedef  int unsigned short 		u16; 
typedef  int signed short  		    s16; 

/*------------------long int------------------------*/
typedef int unsigned long  		    u32;
typedef int signed     long 		s32;
 
/*--------------------float------------------------*/
typedef float  						f32;
typedef double  					f64;
typedef long double 				f128;
/*------------------Patient linked list node---------------*/
typedef struct nodes{
	u8 age;
	u8 *first_name;
	u8 *last_name;
	u8 *gender;/*to be filled with either Female or Male(string)*/
	u32 id;
	struct nodes * next;
}patient;








