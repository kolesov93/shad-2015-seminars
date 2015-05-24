import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Created by svetlana on 30.04.15.
 */
public class Decode {

    static Map<String, Character>map;
    static PrintWriter pw;

    static String decoder(String s, String end) throws FileNotFoundException {
        String builder = "";
        for (int i = 0; i < s.length(); ++i){
            builder += bin(s.charAt(i));
        }
        builder += end;
        String res = "";
        while (builder.length() > 0){
            int n = 1;
            while (!map.containsKey(builder.substring(0,n))){
                ++n;
            }
            String cod = builder.substring(0,n);
            builder = builder.substring(n);
            res += String.valueOf(map.get(cod));
        }
        return res;
    }

    static String bin(char c){
        String s = "";
        for (int i = 0; i < 16; ++i){
            s += String.valueOf((int)c%2);
            c /= 2;
        }
        String res = "";
        for (int i = 0; i < s.length(); ++i){
            res += s.substring(s.length()-i-1, s.length()-i);
        }
        return res;
    }

    public static void main(String[] args) throws IOException {

        Scanner sc = new Scanner(new File("out.txt"));
        int n = sc.nextInt();
        sc.nextLine();
        char[]symb = new char[n];
        for (int i = 0; i < n; ++i){
            symb[i] = sc.nextLine().charAt(0);
        }
        String[] codes = new String[n];
        for (int i = 0; i < n; ++i){
            codes[i] = sc.nextLine();
        }
        map = new HashMap<String, Character>();
        for (int i = 0; i < n; ++i){
            map.put(codes[i], symb[i]);
        }
        String end = sc.nextLine();
        sc.close();
        pw = new PrintWriter("result.txt");
        String toDecode = "";
        byte[]b = java.nio.file.Files.readAllBytes(new File("file.txt").toPath());
        for (int i = 0; i < b.length/2; ++i){
            char c;// = (char)b[2*i];
            if (b[2*i] < 0){
                c = (char)(256+b[2*i]);
            }else {
                c = (char)b[2*i];
            }
            c *= 256;
            char t;// = (char)b[2*i+1];
            if (b[2*i+1] < 0){
                t = (char)(256+b[2*i+1]);
            }else {
                t = (char)b[2*i+1];
            }
            c += t;
            toDecode += String.valueOf(c);
        }
        System.out.print(decoder(toDecode,end));
    }
}
