import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
//		InputStream is=new FileInputStream(new File("/home/belief/桌面/1009/a.in"));
		Scanner scanner=new Scanner(new BufferedInputStream(System.in));
		int T=scanner.nextInt();
		BigInteger two=BigInteger.ONE.add(BigInteger.ONE);
		while(T-->0) {
			BigInteger n=scanner.nextBigInteger();
			if(n.compareTo(BigInteger.ZERO)==0) {
				System.out.println(0);
				continue;
			}
			BigInteger low=BigInteger.ZERO,high=n.add(BigInteger.ONE),mid=BigInteger.ZERO;
			int len=n.toString().length();
			if(len>50) {
				StringBuffer sb=new StringBuffer();
				sb.append('1');
				for(int i=1,t=len/2-1;i<t;++i)sb.append('0');
				low=new BigInteger(sb.toString());
				sb.append('0');
				sb.append('0');
				high=new BigInteger(sb.toString());
			}
			//System.out.println(low);
			//System.out.println(high);
			//System.exit(0);
//			while(low.compareTo(high.subtract(BigInteger.ONE))<0) {
//				mid=(low.add(high)).shiftRight(1);
//				if(mid.multiply(mid).compareTo(n)<=0)low=mid;
//				else high=mid;
//			}
			while(low.compareTo(high)<0) {
				mid=(low.add(high)).shiftRight(1);
				if(mid.multiply(mid).compareTo(n)<=0)low=mid.add(BigInteger.ONE);
				else high=mid.subtract(BigInteger.ONE);
			}
			if(low.multiply(low).compareTo(n)>0)low=low.subtract(BigInteger.ONE);
			//System.out.println(low);
			System.out.println(low.mod(two));
		}
		
		
	}
}

