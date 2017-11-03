
#include"param.h"

/* function to get us to a parameter */
static int scan_achar(FILE* fptr){
   int achar = 0;
   while((achar != EOF) && (achar != '*'))
        achar = fgetc(fptr);
   return achar;
}

/* check to see if we have a good input */
static int check_achar(int achar){
   if(achar == EOF){
      printf("Premature end of data in parameter file");
      exit(13);
   }
   return achar;
}

/* read the parameter file and put the data in the parameter object */
int param_read( char* param_file_name, param_obj *obj) {
     int retval = 0;
     int achar;
     FILE* fptr = fopen(param_file_name,"r");
     if(fptr){
        /* get the propagation speed */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%lf",&obj->c);

        /* get the sample rate */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%lf",&obj->Fs);

        /* get the time series length */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%d",&obj->Nts);

        /* get the sensor spacing */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%lf",&obj->Dsens);

        /* get the number of sensors */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%d",&obj->Nsens);

        /* get the number of averages */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%d",&obj->Navg);

        /* get the number of narrow band simualted tones */
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%d",&obj->Nsim_freqs);
        obj->sim_freqs = (double*)malloc(2 * obj->Nsim_freqs * sizeof(double));
        if(obj->sim_freqs){
             int i;
             obj->sim_bearings = obj->sim_freqs + obj->Nsim_freqs;
             for(i=0; i<obj->Nsim_freqs; i++){
                achar = check_achar(scan_achar(fptr)); /* go to input */
                fscanf(fptr,"%lf",&(obj->sim_freqs[i]));
             }
             for(i=0; i<obj->Nsim_freqs; i++){
                achar = check_achar(scan_achar(fptr)); /* go to input */
                fscanf(fptr,"%lf",&(obj->sim_bearings[i]));
             }
        } else {
            printf("Malloc failure\n");
            retval = 1;
        }
        achar = check_achar(scan_achar(fptr)); /* go to input */
        fscanf(fptr,"%d",&obj->Nsim_noise);
     } else {
        fprintf(stderr,"File open error in param_read \n");
        fflush(stdout);
        retval = 1;
     }
     return retval;
}

void param_free(param_obj* obj){
    if(obj->sim_freqs) free(obj->sim_freqs);
}

void param_log(param_obj* obj){
    int i;
    printf("c: %f\n",(float)obj->c);
    printf("Fs: %f\n",(float)obj->Fs);
    printf("Nts: %d\n",(int)obj->Nts);
    printf("Dsens: %f\n",(float)obj->Dsens);
    printf("Nsens: %d\n",(int)obj->Nsens);
    printf("Navg: %d\n",(int)obj->Navg);
    printf("Nsim_noise %d\n",(int)obj->Nsim_noise);
    printf("Nsim_freqs %d\n",(int)obj->Nsim_freqs);
    for(i=0; i<obj->Nsim_freqs; i++)
        printf("Narrow Band Signal %d: %fHz at %f deg\n",
                  i,(float)obj->sim_freqs[i],(float)obj->sim_bearings[i]);
}
