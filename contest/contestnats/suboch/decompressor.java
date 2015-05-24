import java.io.*;
import java.sql.Array;
import java.util.*;



class decompressor {

    static HashMap<Byte, Integer> freqMap;
    static HashMap<Byte, String> HafTab;
    static BitSet out;
    static PriorityQueue<freqNode> freqQueue;
    static freqNode root = null;

    static class freqNode implements Comparable<freqNode> {
        Byte sym;
        int freq;
        freqNode rightS;
        freqNode leftS;


        public freqNode(freqNode a, freqNode b) {
            sym = null;
            freq = a.freq + b.freq;
            rightS = b;
            leftS = a;
        }

        public freqNode(Byte s, int fr) {
            sym = s;
            freq = fr;
            rightS = null;
            leftS = null;
        }

        public String toString() {
            return sym.toString() + " " + (freq);
        }

        public int compareTo(freqNode o) {
            return (this.freq - o.freq);
        }
    }

    static void hafTreeProc(freqNode r, String curStr) {
        if (r.sym != null) {
            HafTab.put(r.sym, curStr);
            return;
        }

        if (r.leftS != null)
            hafTreeProc(r.leftS, curStr + '0');
        if (r.rightS != null)
            hafTreeProc(r.rightS, curStr + '1');

        return;
    }

    static public void main(String[] args) throws IOException {

        byte[] A = null;
        byte[] BWTT = null;
        DataInputStream inFile = new DataInputStream(System.in);

        int len = inFile.readInt();
        int blen = inFile.readInt();
        int ThreeSize = inFile.readInt();
        freqMap = new HashMap<Byte, Integer>();
        freqMap.clear();
        for(int i = 0; i < ThreeSize; i++){
            Byte b = inFile.readByte();
            int f = inFile.readInt();
            freqMap.put(b,f);
        }

        freqQueue = new PriorityQueue<freqNode>();
        for (Byte x : freqMap.keySet()) {
            freqQueue.add(new freqNode(x, freqMap.get(x)));
        }

        while (freqQueue.size() > 1) {
            freqNode t1 = freqQueue.remove();
            freqNode t2 = freqQueue.remove();
            freqNode tmpRoot = new freqNode(t1, t2);
            freqQueue.add(tmpRoot);
        }
        root = freqQueue.remove();
        HafTab = new HashMap<Byte, String>();
        hafTreeProc(root, "");

        byte[] zFile = new byte[len];
        for(int i =0; i< blen;i++)
            zFile[i] = inFile.readByte();
        BitSet bitStr = BitSet.valueOf(zFile);
        byte[] Buf = new byte[len];
        freqNode curN = root;
        int j = 0;
        int t = 0;
        for(t = 0; t< len;){
            if(curN.sym != null){
                Buf[t] = ((curN.sym));
                curN = root;
                t++;
            }
            else{
                if(bitStr.get(j)){
                    curN = curN.rightS;
                }
                else curN = curN.leftS;

                j++;
            }
        }
        DataOutputStream outFile = new DataOutputStream(System.out);
        outFile.write(Buf);

    }
}
