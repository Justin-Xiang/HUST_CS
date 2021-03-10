import prettytable as pt
def fenghan(t,v):
    fenghan = 35.74+0.6215*t-35.75*(v**0.16)+0.4275*t*(v**0.16)
    return fenghan
tb = pt.PrettyTable()
tb.field_names = ["temperatue \ velocity", "0", "5", "10","15","20","25","30","35","40","45","50"]
for t in range(-20,60,10):
     tb.add_row([t, fenghan(t,0),fenghan(t,5),fenghan(t,10),fenghan(t,15),fenghan(t,20),fenghan(t,25),fenghan(t,30),fenghan(t,35),fenghan(t,40),fenghan(t,45),fenghan(t,50)])
print(tb)