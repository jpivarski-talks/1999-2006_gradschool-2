      function fitfunc(invm)
      common/pawpar/par(2)

      real invm,mn,mlsp,ep2
      real p,hold,mz
      real gnij,hold2,en,pole
      real ep1

      mz=91.1882
      mlsp=107.697
      mn=par(2)+mlsp
      ep1=1.0
      ep2=-1.0

      p=mn*mn*mn*mn
      p=p+mlsp*mlsp*mlsp*mlsp
      p=p+invm*invm*invm*invm
      p=p-2.0*mn*mn*invm*invm
      p=p-2.0*mn*mn*mlsp*mlsp
      p=p-2.0*invm*invm*mlsp*mlsp
      if(p.lt.0.0) then
         fitfunc=0.0
         return
      endif 
      p=sqrt(p)/(2.0*mn)
      
      pole=(invm*invm-mz*mz)
      
      hold=mn*mn*mn*mn
      hold=hold+mlsp*mlsp*mlsp*mlsp
      hold=hold+invm*invm*mlsp*mlsp
      hold=hold-2.0*invm*invm*invm*invm
      hold=hold+mn*mn*(invm*invm-2.0*mlsp*mlsp)
      hold=hold+6.0*ep1*ep2*invm*invm*mn*mlsp
      
      hold=hold*invm*p
      hold=hold/(mlsp*mlsp*pole*pole)
      
      fitfunc=par(1)*hold
      return 
      end
