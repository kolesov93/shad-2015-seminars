import java.io.*;
import java.sql.Array;
import java.util.*;



class compressor {

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

        DataInputStream inFile = new DataInputStream(System.in);

        int inFlag = 1;
        int ind = 0;
        byte[] HafMas = null;

        while (inFlag == 1) {
            byte y = (byte) System.in.read();
            int u = System.in.available();
            if (HafMas == null) HafMas = new byte[u+1];
            HafMas[ind] = y;
            ind++;
            if (ind == HafMas.length) break;
        }


        if (freqMap != null)
            freqMap.clear();
        freqMap = new HashMap<Byte, Integer>();
        for (int i = 0; i < HafMas.length; i++) {
            Byte curSym = HafMas[i];
            if (freqMap.get(curSym) != null)
                freqMap.put(curSym, freqMap.get(curSym) + 1);
            else freqMap.put(curSym, 1);
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

        out = new BitSet();

        int curInd = 0;
        for (int i = 0; i < HafMas.length; i++) {
            Byte curSym = HafMas[i];
            String bitStr = HafTab.get(curSym);
            for(int j = 0; j < bitStr.length(); j++){
                out.set(curInd+j, (bitStr.charAt(j) - '0') != 0);
            }
            curInd += bitStr.length();
        }
        byte[] outStr = out.toByteArray();
        BitSet outT = BitSet.valueOf(outStr);
        DataOutputStream outFile = new DataOutputStream(System.out);
        int blen = out.toByteArray().length;
        outFile.writeInt((int) (HafMas.length));
        outFile.writeInt(blen);
        outFile.writeInt((int)(freqMap.keySet().size()));
        for (Byte x : freqMap.keySet()) {
            outFile.writeByte(x);
            outFile.writeInt(freqMap.get(x));
        }

        outFile.write(out.toByteArray());

    }
}
