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
public class Main {

    static int len = 26*2+10;
    static int[]val;
    static char[]key;
    static Object[]obj;
    static Map<Node, String>m;
    static PrintWriter pw;
    static StringBuilder res;

    public static void sort(){
        for (int i = 0; i < val.length; ++i){
            for (int j = 1; j < val.length; ++j){
                if (val[j-1] > val[j]){
                    int temp = val[j-1];
                    val[j-1] = val[j];
                    val[j] = temp;
                    Object tmp = obj[j-1];
                    obj[j-1] = obj[j];
                    obj[j] = tmp;
                }
            }
        }
    }

    static void inOrder(Node root,String s){
        m.put(root, s);
        if (root.lson != null){
            inOrder(root.lson, s + "0");
        }
        if (root.rson != null){
            inOrder(root.rson, s + "1");
        }
    }

    static char parseChar(String s){
        int n = 0;
        for (int i = 0; i < s.length(); ++i){
            n *= 2;
            n += Integer.parseInt(s.substring(i,i+1));
        }
        return (char)n;
    }

    static String parseText(String s){
        while (s.length() >= 16){
            String symb = s.substring(0,16);
            s = s.substring(16);
            res.append(parseChar(symb));
        }
        return s;
    }

    static Map<Character, Integer> getStaticstics(Scanner sc){
        Map<Character, Integer> map = new HashMap<Character, Integer>();
        while (sc.hasNext()){
            String line = sc.nextLine();
            for (int i = 0; i < line.length(); ++i){
                int count = 0;
                if (map.containsKey(line.charAt(i))){
                    count = map.get(line.charAt(i));
                }
                map.put(line.charAt(i), count+1);
            }

        }
        return map;
    }

    public static void main(String[] args) throws IOException {
        res = new StringBuilder();
        Scanner sc = new Scanner(new File("alice.txt"));
        pw = new PrintWriter(new File("out.txt"));
        Map<Character, Integer> map = getStaticstics(sc);
        val = new int[map.size()];
        key = new char[map.size()];
        int idx = 0;
        for (Character c : map.keySet()){
            key[idx++] = c;
        }
        idx = 0;
        for (Integer i: map.values()){
            val[idx++] = i;
        }
        obj = new Object[key.length];
        idx = 0;
        for (char c: key){
            obj[idx++] = Character.valueOf(c);
        }
        sort();
        Node root = new Node('&');
        while(obj.length > 1){
            Node n = new Node('&');
            if (obj[0].getClass() == root.getClass()){
                n.lson = (Node)obj[0];
                ((Node)obj[0]).father = n;
            }else {
                n.lson = new Node((Character)obj[0]);
                n.lson.father = n;
            }
            if (obj[1].getClass() == root.getClass()){
                n.rson = (Node)obj[1];
                ((Node)obj[1]).father = n;
            }else {
                n.rson = new Node((Character)obj[1]);
                n.rson.father = n;
            }
            int value = val[0] + val[1];
            Object newObj[] = new Object[obj.length-1];
            int newVal[] = new int[val.length-1];
            newObj[0] = n;
            newVal[0] = value;
            for (int i = 2; i < val.length; ++i){
                newObj[i-1] = obj[i];
                newVal[i-1] = val[i];
            }
            obj = newObj;
            val = newVal;
            sort();
        }
        root = (Node)obj[0];
        m = new HashMap<Node, String>();
        inOrder(root, "");
        int n = 0;
        for (Node node : m.keySet()){
            if (node.c != '&'){
                ++n;
            }
        }
        char[]symb = new char[n];
        String[]codes = new String[n];
        idx = 0;
        Node[] nodeArr = m.keySet().toArray(new Node[m.size()]);
        String[] nodeString = m.values().toArray(new String[m.size()]);
        for (int i = 0; i < nodeArr.length; ++i){
            if (nodeArr[i].c != '&'){
                symb[idx++] = nodeArr[i].c;
                codes[idx-1] = nodeString[i];
            }
        }
        Map<Character,String> dict = new HashMap<Character, String>();
        for (int i = 0; i < n; ++i){
            dict.put(symb[i], codes[i]);
        }
        String text = "";
        sc.close();
        Scanner read = new Scanner(new File("alice.txt"));
        while (read.hasNext()){
            String line = read.nextLine();
            for (int i = 0; i < line.length(); ++i){
                text += dict.get(line.charAt(i));
            }
            text = parseText(text);
        }
        byte[] data = new byte[res.length() * 2];
        for (int i = 0; i < res.length(); ++i) {
            data[2 * i] = (byte)(res.charAt(i) / 256);
            data[2 * i + 1] = (byte)(res.charAt(i) % 256);
        }
        java.nio.file.Files.write(new File("file.txt").toPath(), data);
        pw.println(symb.length);
        for (int i = 0; i < symb.length; ++i){
            pw.println(symb[i]);
        }
        for (int i = 0; i < symb.length; ++i){
            pw.println(codes[i]);
        }
        pw.println(text);
        pw.close();
    }
}

class Node{
    char c;
    Node rson;
    Node lson;
    Node father;

    Node(char ch){
        c = ch;
    }
}
