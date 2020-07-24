      function cfunc(x)
      common/pawpar/par(3)
      real p, mw, m1, m2

C par(1) is norm
C par(2) is A
C par(3) is m2-m1

      mw = 80.419
      m1 = 106.547
      m2 = m1 + par(3)

      if (x.gt.par(3)) then
         cfunc = 0
         return
      endif

      p = sqrt(((m2**2 + m1**2 - x**2)/2/m2)**2 - m1**2)
      
      cfunc = m1**4 + m2**4 + x**2*m2**2 - 2*x**4 + m1**2*(x**2-2*m2**2)
      cfunc = cfunc - 6*par(2)*x**2*m1*m2
      cfunc = cfunc * par(1) * (x*p/m2**2/(x**2-mw**2)**2)

      return
      end
