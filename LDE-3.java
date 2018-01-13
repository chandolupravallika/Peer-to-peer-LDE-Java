import java.util.*;
class LDE {
    public static void main(String[] args) {
        int a, b, c, m; //m=no of nodes
        String[] resources = {
            "Telugu",
            "Hindi",
            "Malyalam",
            "Bengali",
            "English"
        };
        HashMap<String,Integer> res = new HashMap<>();
        for (int k = 0; k < resources.length; k++) {
            res.put(resources[k], k);
        }
        HashMap<Integer,String> hm = new HashMap<>();
        try{
        Scanner sc = new Scanner(System.in);
        System.out.println("The congruence eqaution is ax=>b(modc)");
        System.out.println("Enter a value from above equation");
        a = sc.nextInt();
        System.out.println("Enter b value from above equation");
        b = sc.nextInt();
        System.out.println("Enter mod value ie c value from above equation");
        c = sc.nextInt();
        int a1 = a, b1 = b, c1 = c;
        //finding gcd
        int rem = 1;
        String ass = new String();

        while (c1 != 0) {
            rem = a1 % c1;
            a1 = c1;
            c1 = rem;
        }
        if (b1 % a1 != 0) {
            System.out.println("Cannot find the logical address for the given congruence");
            System.exit(1);
        } else {
            int gcd = a1;
            //creating group heads
           for(int i=0;i<70;i++)
                {
                System.out.print("\u2500");
                }
            System.out.println("\n" + "Creating Group heads/Cluster heads:" +"\n");
            int[][] groups = new int[gcd][gcd];
            System.out.format("%12s%21s%17s", "Resourcetype", "Logical Address", "Ipaddress" +"\n");
            for (int t = 0, n0 = 1; t < gcd; t++) {
                //System.out.println("hi");
                int x = (n0 + ((c * t) / gcd));
                groups[t][0] = x;
                String resourcetype = resources[t];
                Random r = new Random();
                String ipaddress=Integer.toString(r.nextInt(256)) + "." + Integer.toString(r.nextInt(256)) + "." + Integer.toString(r.nextInt(256)) + "." + Integer.toString(r.nextInt(256));
                System.out.format("%10s%22d%22s", resourcetype, groups[t][0], ipaddress);
                //System.out.println(groups[t][0]);
            }
            //creating peers of each cluster
            for (int t = 0, n0 = 1; t < gcd; t++) {
                for(int i=0;i<70;i++)
                {
                System.out.print("\u2500");
                }
                System.out.print("\n"+"Creating nodes for cluster:");
                System.out.print(groups[t][0] + "\n");
                String resourcetype=resources[t];
                System.out.print("\n"+"Values for Resource Type " + resourcetype +"\n" +"\n");
                System.out.format("%5s%15s", "Logical Address", "Value");
                System.out.print("\n");


                ass = resources[t];
                for (m = 0; m < gcd; m++) {
                    int x1 = (n0 + ((c * t) / gcd) + (m * c));
                    groups[t][m] = x1;
                    String req = ass.charAt(0) + Integer.toString(m + 1);
                    String dis=Integer.toString(groups[t][m]);
                    System.out.format("%10s%18s",dis,req);
                    System.out.print("\n");
                    hm.put(x1, req);
                }

            }

            while (1 > 0) {
                Scanner num = new Scanner(System.in);
                System.out.println("\n"+"which search do you want to perform" + "\n" + "1.Node-Node Searching" + "\n" + "2.Inter-Node Searching" + "\n" + "Select the number 1 or 2");
                int choice;
                choice = num.nextInt();
                if (choice == 1) {

                    /*node-node searching*/
                    Scanner sd = new Scanner(System.in);
                    System.out.println("Enter the resource type(Telugu,Hindi..):");
                    String resourcein;
                    resourcein = sd.nextLine();
                    System.out.println("Enter the value to be searched(T3,E4..):");
                    String valuein;
                    valuein = sd.nextLine();
                    int flagg = 0;
                    /*finding group to be searched from resource*/
                        int groupid = (int) res.get(resourcein);
                        for (int k = 0; k < groups[groupid].length; k++) {
                            String comp = (String) hm.get(groups[groupid][k]);
                            if (comp.equals(valuein)) {
                                flagg = 1;
                                System.out.println("The Requested value is found at logical address "+groups[groupid][k]);
                              

                                break;

                            }
                        }
                        if (flagg == 0) {
                            System.out.println("The Requested value is not found. Please check if the requested value is correct");
                        }
                } else {
                    /*internode Searching*/
                    Scanner sid = new Scanner(System.in);
                    System.out.println("Enter the resource type(Telugu,English...):");
                    String resourceid;
                    resourceid = sid.nextLine();
                    System.out.println("Enter the logical address of the peer(1,26,6..):");
                    String valueid;
                    valueid = sid.nextLine();
                    System.out.println("Enter the requested resource type(Telugu,English...):");
                    String reqid;
                    reqid = sid.nextLine();
                    System.out.println("Enter the value to be searched(E3,T4,B3):");
                    String searchid;
                    searchid = sid.nextLine();
                        int headid = (int) res.get(resourceid);
                        int peerheadid = (int) res.get(reqid);
                        int h = (headid - peerheadid);
                        String comp = (String) hm.get(Integer.parseInt(valueid));

                        if (comp.equals(searchid)) {
                            System.out.println("Error:The Requested value is found at the same address");
                        } else {
                            if (Math.abs(h) > gcd / 2) {
                                int flag = 0;
                                for (int k = 0; k < groups[peerheadid].length; k++) {

                                    comp = (String) hm.get(groups[peerheadid][k]);
                                    if (comp.equals(searchid)) {
                                        flag = 1;
                                        int answer = peerheadid + 1;
                                        if (h != 0) {
                                            System.out.println("The Requested value is found in group " + answer + " at logical address " + groups[peerheadid][k] + " in reverse searching order");
                                        } else {
                                            System.out.println("The Requested value is found in the same group " + answer + " at logical address " + groups[peerheadid][k]);

                                        }
                                        break;
                                    }
                                }
                                if (flag == 0) {
                                    System.out.println("Search Failed");
                                }
                            } else {
                                int flag = 0;
                                for (int k = 0; k < groups[peerheadid].length; k++) {

                                    comp = (String) hm.get(groups[peerheadid][k]);
                                    if (comp.equals(searchid)) {
                                        flag = 1;
                                        int answer = peerheadid + 1;
                                        if (h != 0) {
                                            System.out.println("The Requested value is found in group " + answer + " at logical address " + groups[peerheadid][k] + " in forward searching order");
                                        } else {
                                            System.out.println("The Requested value is found in the same group " + answer + " at logical address " + groups[peerheadid][k]);

                                        }
                                        break;

                                    }
                                }
                                if (flag == 0) {
                                    System.out.println("Search Failed");
                                }

                            }
                        }
                }

                Scanner repeat = new Scanner(System.in);
                System.out.println("Do you want to perform another search? select y/n ");
                String fi;
                fi = repeat.nextLine();

                char repeatsearch = fi.charAt(0);
                if (repeatsearch == 'n' || repeatsearch == 'N') {
                    break;
                }
            }
        }
    }
    catch(Exception e)
    {
        System.out.println("Invalid Value entered or Wrong Resource selected. Please Correct it");
    }
    }
}