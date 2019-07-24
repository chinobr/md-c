
  KE*=0.5;
 

    KE = 0.0;
    for (i=0;i<N;i++) {
      if (gsl_rng_uniform(r) < nu*dt) 
{
	vx[i]=gsl_ran_gaussian(r,sigma);
	vy[i]=gsl_ran_gaussian(r,sigma);
	vz[i]=gsl_ran_gaussian(r,sigma);
      }

      KE+=vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
    }
    KE*=0.5;
    TE=PE+KE;
    fprintf(stdout,"%i %.5lf %.5lf %.5lf %.5lf %.5le %.5lf %.5lf\n",
	    s,s*dt,PE,KE,TE,(TE-TE0)/TE0,KE*2/3./N,rho*KE*2./3./N+vir/3.0/V);
    if (!(s%fSamp)) {
      sprintf(fn,"%i.xyz",!strcmp(wrt_code_str,"a")?0:s);
      out=fopen(fn,wrt_code_str);
      xyz_out(out,rx,ry,rz,vx,vy,vz,ix,iy,iz,L,N,16,1,unfold);
      fclose(out);


