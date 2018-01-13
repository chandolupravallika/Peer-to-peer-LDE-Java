using System;
using System.Collections.Generic;  
public class LDE 
{  
        public static void Main() 
        {
                int a,b,c,m;//m=no of nodes;
                String[] resources = new String[] { 
                  "Telugu",
                  "Hindi",
                  "Malyalam",
                  "Bengali",
                  "English"
                };
              Dictionary<String, int> res = new Dictionary<String, int>();
              Dictionary<int,String> hm = new Dictionary<int,String>();
               for (int k = 0; k < resources.Length; k++) {
                res.Add(resources[k], k);
              }
              Console.WriteLine("The congruence eqaution is ax=>b(modc)");
              Console.WriteLine("Enter a value from above equation");
              try
              {
                  a = int.Parse(Console.ReadLine());
                  Console.WriteLine("Enter b value from above equation");  
                  b = int.Parse(Console.ReadLine());
                  Console.WriteLine("Enter mod value ie c value from above equation"); 
                  c= int.Parse(Console.ReadLine());
                  

                  int a1 = a, b1 = b, c1 = c;
                  //finding gcd
                  int rem = 1;
                  String ass;
                  while (c1 != 0) {
                  rem = a1 % c1;
                  a1 = c1;
                  c1 = rem;
                  }
                  if (b1 % a1 != 0) {
                  Console.WriteLine("Cannot find the logical address for the given congruence");
                  Environment.Exit(1);
                  }
                  else {
                  int gcd = a1;
                  //creating group heads
                    for(int i=0;i<70;i++)
                      {
                      Console.Write("\u2500");
                      }
                      Console.WriteLine("\n" + "Creating Group heads/Cluster heads:" +"\n");
                      int[,] groups = new int[gcd,gcd];
                      String output=String.Format("{0,10} {1,18} {2,18}\n\n", "Resourcetype", "Logical Address", "Ipaddress");
                      Random r = new Random();
                    for (int t = 0, n0 = 1; t < gcd; t++) {
                      //System.out.println("hi");
                      int x = (n0 + ((c * t) / gcd));
                      groups[t,0] = x;
                      String resourcetype = resources[t];
                      String ipaddress=r.Next(1,256).ToString() + "." + r.Next(1,256).ToString() + "." + r.Next(1,256).ToString() + "." + r.Next(1,256).ToString();
                      output+=String.Format("{0,10}{1,16}{2,25}\n", resourcetype, groups[t,0], ipaddress);
                      //System.out.println(groups[t][0]);
                    }
                    Console.Write(output);
                    //creating peers of each cluster
                for (int t = 0, n0 = 1; t < gcd; t++) {
                    for(int i=0;i<70;i++)
                    {
                    Console.Write("\u2500");
                    }
                    Console.WriteLine("\n"+"Creating nodes for cluster:");
                    Console.WriteLine(groups[t,0] + "\n");
                    String resourcetype=resources[t];
                    Console.WriteLine("\n"+"Values for Resource Type " + resourcetype +"\n" +"\n");
                    output=String.Format("{0,8}{1,12}\n", "Logical Address", "Value");
                    ass = resources[t];
                    for (m = 0; m < gcd; m++) {
                        int x1 = (n0 + ((c * t) / gcd) + (m * c));
                        groups[t,m] = x1;
                        String req = (ass[0]).ToString() + (m + 1).ToString();
                        String dis=(groups[t,m]).ToString();
                        output+=String.Format("{0,8}{1,12}\n",dis,req);
                        hm.Add(x1, req);
                    }
                    Console.Write(output);

                }
             
                while (1 > 0) {
                    Console.WriteLine("\n"+"which search do you want to perform" + "\n" + "1.Node-Node Searching" + "\n" + "2.Inter-Node Searching" + "\n" + "Select the number 1 or 2");
                    int choice;
                    choice = int.Parse(Console.ReadLine());
                    if (choice == 1) {

                        /*node-node searching*/
                       String resourcein;
                       String valuein;
                      int flagg = 0;
                        Console.WriteLine("Enter the resource type(Telugu,Hindi..):");
                        resourcein = Console.ReadLine();
                        Console.WriteLine("Enter the value to be searched(T3,E4..):");
                        valuein = Console.ReadLine();
                        /*finding group to be searched from resource*/
                            int groupid = (int) res[resourcein];
                            for (int k = 0; k < groups.GetLength(0); k++) {
                                String comp = (String) hm[groups[groupid,k]];
                                if (comp.Equals(valuein)) {
                                    flagg = 1;
                                    Console.WriteLine("The Requested value is found at logical address "+groups[groupid,k]);
                                  

                                    break;

                                }
                            }
                            if (flagg == 0) {
                                Console.WriteLine("The Requested value is not found. Please check if the requested value is correct");
                            }
                    } else {
                        /*internode Searching*/
                      String resourceid;
                      String valueid;
                      String reqid;
                      String searchid;
                        Console.WriteLine("Enter the resource type(Telugu,English...):");
                        resourceid = Console.ReadLine();
                        Console.WriteLine("Enter the logical address of the peer(1,26,6..):");
                        valueid = Console.ReadLine();
                        Console.WriteLine("Enter the requested resource type(Telugu,English...):");
                        reqid = Console.ReadLine();
                        Console.WriteLine("Enter the value to be searched(E3,T4,B3):");
                        searchid = Console.ReadLine();
                            int headid = (int) res[resourceid];
                            int peerheadid = (int) res[reqid];
                            int h = (headid - peerheadid);
                            String comp = (String) hm[int.Parse(valueid)];

                            if (comp.Equals(searchid)) {
                                Console.WriteLine("Error:The Requested value is found at the same address");
                            } else {
                                if (Math.Abs(h) > gcd / 2) {
                                    int flag = 0;
                                    for (int k = 0; k < groups.GetLength(0); k++) {

                                        comp = (String) hm[groups[peerheadid,k]];
                                        if (comp.Equals(searchid)) {
                                            flag = 1;
                                            int answer = peerheadid + 1;
                                            if (h != 0) {
                                                Console.WriteLine("The Requested value is found in group " + answer + " at logical address " + groups[peerheadid,k] + " in reverse searching order");
                                            } else {
                                                Console.WriteLine("The Requested value is found in the same group " + answer + " at logical address " + groups[peerheadid,k]);

                                            }
                                            break;
                                        }
                                    }
                                    if (flag == 0) {
                                        Console.WriteLine("Search Failed");
                                    }
                                } else {
                                    int flag = 0;
                                    for (int k = 0; k < groups.GetLength(0); k++) {

                                        comp = (String) hm[groups[peerheadid,k]];
                                        if (comp.Equals(searchid)) {
                                            flag = 1;
                                            int answer = peerheadid + 1;
                                            if (h != 0) {
                                                Console.WriteLine("The Requested value is found in group " + answer + " at logical address " + groups[peerheadid,k] + " in forward searching order");
                                            } else {
                                                Console.WriteLine("The Requested value is found in the same group " + answer + " at logical address " + groups[peerheadid,k]);

                                            }
                                            break;

                                        }
                                    }
                                    if (flag == 0) {
                                        Console.WriteLine("Search Failed");
                                    }

                                }
                            }
                    }
                    Console.WriteLine("Do you want to perform another search? select y/n ");
                    String fi;
                    fi = Console.ReadLine();

                    char repeatsearch = fi[0];
                    if (repeatsearch == 'n' || repeatsearch == 'N') {
                        break;
                    }
                }
              }
          }

          catch(Exception)
          {
                Console.WriteLine("Wrong Resource type selected or incorrect input given Please Correct it");
                Environment.Exit(0);
          }

        }

}