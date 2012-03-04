def scan_achar(fptr):
   l=str()
   while not l.startswith('*'):
        l=fptr.readline()
   return l

def param_read( param_file_name):
     fptr = open(param_file_name,"r");
     obj={'c':1,'Fs':2,'Nts':3,'Dsens':4,'Nsens':5,'Navg':6,
           'Nsim_freqs':'7','sim_freqs':[],'sim_bearings':[],'Nsim_noise':10}
     # get the propagation speed
     l=scan_achar(fptr)
     obj['c']=float(l.partition('*')[2].partition(' ')[0])
     # get the sample rate
     l=scan_achar(fptr)
     obj['Fs']=float(l.partition('*')[2].partition(' ')[0])
     # get the time series length */
     l=scan_achar(fptr)
     obj['Nts']=int(l.partition('*')[2].partition(' ')[0])
     # get the sensor spacing */
     l=scan_achar(fptr)
     obj['Dsens']=float(l.partition('*')[2].partition(' ')[0])
     # get the number of sensors */
     l=scan_achar(fptr)
     obj['Nsens']=int(l.partition('*')[2].partition(' ')[0])
     # get the number of averages */
     l=scan_achar(fptr)
     obj['Navg']=int(l.partition('*')[2].partition(' ')[0])
     # get the number of narrow band simualted tones */
     l=scan_achar(fptr)
     obj['Nsim_freqs']=int(l.partition('*')[2].partition(' ')[0])
     n=obj['Nsim_freqs']
     sim_freqs = []
     for i in range(n):
         l=scan_achar(fptr)
         sim_freqs += [float(l.partition('*')[2].partition(' ')[0])]
     obj['sim_freqs']=sim_freqs
     sim_bearings = []
     for i in range(n):
         l=scan_achar(fptr)
         sim_bearings += [float(l.partition('*')[2].partition(' ')[0])]
     obj['sim_bearings']=sim_bearings
     # Nsim_noise
     l=scan_achar(fptr)
     obj['Nsim_noise']=int(l.partition('*')[2].partition(' ')[0])
     fptr.close()
     return obj
