import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Compressor {
    public static void main(String[] args) throws IOException {
        String inFile = args[0];
        String outFile = args[1];

        String text = new String(Files.readAllBytes(Paths.get(inFile)));
        text = text.substring(0, text.length() - 1);

        bwtRleHuf(text);
        bwtMtf2RleHuf(text);
        rleBwtRleHuf(text);
        bwtMtf2Huf(text);

        FileOutputStream out = new FileOutputStream(outFile);
        out.write(toOut);
        out.close();
    }

    static int min = Integer.MAX_VALUE;
    static byte[] toOut;

    static void bwtRleHuf(String source) {
        try {
            String encodedText = BWT.encode(source);
            encodedText = RLE.encode(encodedText);
            byte[] encoded = Huffman.encode("1 " + BWT.our + " " + encodedText);
            if (encoded.length < min) {
                toOut = encoded;
                min = encoded.length;
            }
        } catch (Throwable t) {
        }
    }

    static void bwtMtf2RleHuf(String source) {
        try {
            String encodedText = BWT.encode(source);
            encodedText = MTF2.encode(encodedText);
            encodedText = RLE.encode(encodedText);
            byte[] encoded = Huffman.encode("2 " + BWT.our + " " + encodedText);
            if (encoded.length < min) {
                toOut = encoded;
                min = encoded.length;
            }
        } catch (Throwable t) {
        }
    }

    static void rleBwtRleHuf(String source) {
        try {
            String encodedText = RLE.encode(source);
            encodedText = BWT.encode(encodedText);
            encodedText = RLE.encode(encodedText);
            byte[] encoded = Huffman.encode("3 " + BWT.our + " " + encodedText);
            if (encoded.length < min) {
                toOut = encoded;
                min = encoded.length;
            }
        } catch (Throwable t) {
        }
    }

    static void bwtMtf2Huf(String source) {
        try {
            String encodedText = BWT.encode(source);
            encodedText = MTF2.encode(encodedText);
            byte[] encoded = Huffman.encode("4 " + BWT.our + " " + encodedText);
            if (encoded.length < min) {
                toOut = encoded;
                min = encoded.length;
            }
        } catch (Throwable t) {
        }
    }

    public static class RLE {
        public static String encode(String source) {
            StringBuilder dest = new StringBuilder();
            for (int i = 0; i < source.length(); i++) {
                int runLength = 1;
                while (i + 1 < source.length() && source.charAt(i) == source.charAt(i + 1)) {
                    runLength++;
                    i++;
                }
                dest.append(runLength);
                dest.append(source.charAt(i));
            }
            return dest.toString();
        }

        public static String decode(String source) {
            StringBuilder dest = new StringBuilder();
            Pattern pattern = Pattern.compile("[0-9]+|[^0-9]");
            Matcher matcher = pattern.matcher(source);
            while (matcher.find()) {
                int number = Integer.parseInt(matcher.group());
                matcher.find();
                try {
                    while (number-- != 0) {
                        dest.append(matcher.group());
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            return dest.toString();
        }
    }

    public static class MTF3 {

        static String symTable = "1234567890 abcdefghijklmnopqrstuvwxyz.':,!?\"()ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        public static String encode(String msg) {
            StringBuilder output = new StringBuilder();
            StringBuilder s = new StringBuilder(symTable);
            for (char c : msg.toCharArray()) {
                int idx = s.indexOf("" + c);
                s = s.deleteCharAt(idx).insert(0, c);
                //if(idx>47)idx+=10;
                output.append((char) idx);
            }
            return output.toString();
        }

        public static String decode(String idxs) {
            StringBuilder output = new StringBuilder();
            StringBuilder s = new StringBuilder(symTable);
            for (int idx : idxs.toCharArray()) {
                //if(idx>47)idx-=10;
                char c = s.charAt(idx);
                output = output.append(c);
                s = s.deleteCharAt(idx).insert(0, c);
            }
            return output.toString();
        }
    }

    public static class MTF2 {

        static String symTable = " abcdefghijklmnopqrstuvwxyz.':,!?\"()ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        public static String encode(String msg) {
            StringBuilder output = new StringBuilder();
            StringBuilder s = new StringBuilder(symTable);
            for (char c : msg.toCharArray()) {
                int idx = s.indexOf("" + c);
                s = s.deleteCharAt(idx).insert(0, c);
                if (idx > 47) idx += 10;
                output.append((char) idx);
            }
            return output.toString();
        }

        public static String decode(String idxs) {
            StringBuilder output = new StringBuilder();
            StringBuilder s = new StringBuilder(symTable);
            for (int idx : idxs.toCharArray()) {
                if (idx > 47) idx -= 10;
                char c = s.charAt(idx);
                output = output.append(c);
                s = s.deleteCharAt(idx).insert(0, c);
            }
            return output.toString();
        }
    }


    public static class BWT {
        public static String encode(String source) {
            int len = source.length();
            int[] suf = suffix(source);
            StringBuilder dest = new StringBuilder();

            for (int i = 0; i < len; ++i) {
                dest.append(source.charAt((suf[i] - 1 + len) % len));
                if (suf[i] == 0) {
                    our = i;
                }
            }
            return dest.toString();
        }

        public static int our;

        public static String decode(String last) {
            char[] chars = last.toCharArray();
            Arrays.sort(chars);
            String first = new String(chars);

            int len = last.length();
            int[] t = new int[len];

            int alf = 91;
            char min = ' ';
            int[] c = new int[alf];
            char x = '^';
            for (int i = 0; i < len; ++i) {
                if (x != first.charAt(i)) {
                    x = first.charAt(i);
                    c[x - min] = i;
                }
            }
            for (int i = 0; i < len; ++i) {
                t[c[last.charAt(i) - min]++] = i;
            }
            StringBuilder dest = new StringBuilder();
            for (int i = 0; i < len; ++i) {
                dest.append(first.charAt(our));
                our = t[our];
            }

            return dest.toString();
        }

        public static int[] suffix(String oldS) {
            int alf = 91;
            char min = ' ';
            int n = oldS.length();
            int max = Math.max(n, alf);

            int[] suf = new int[n];
            int[] c = new int[n];
            int[] buck = new int[max];
            int[] temp = new int[n];
            int[] temp2 = new int[n];

            for (int i = 0; i < n; ++i) {
                ++buck[oldS.charAt(i) - min];
            }

            for (int i = 1; i < alf; ++i) {
                buck[i] = buck[i] + buck[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                int k = oldS.charAt(i) - min;
                --buck[k];
                suf[buck[k]] = i;
            }

            c[suf[0]] = 0;
            int classes = 1;
            for (int i = 1; i < n; ++i) {
                if (oldS.charAt(suf[i]) != oldS.charAt(suf[i - 1])) ++classes;
                c[suf[i]] = classes - 1;
            }

            for (int h = 0; (1 << h) < n; ++h) {
                for (int i = 0; i < n; ++i) {
                    temp[i] = suf[i] - (1 << h);
                    if (temp[i] < 0) temp[i] += n;
                }
                Arrays.fill(buck, 0);

                for (int i = 0; i < n; ++i) {
                    ++buck[c[temp[i]]];
                }
                for (int i = 1; i < classes; ++i) {
                    buck[i] = buck[i - 1] + buck[i];
                }
                for (int i = n - 1; i >= 0; --i) {
                    --buck[c[temp[i]]];
                    suf[buck[c[temp[i]]]] = temp[i];
                }

                temp2[suf[0]] = 0;
                classes = 1;
                for (int i = 1; i < n; ++i) {
                    int mid1 = (suf[i] + (1 << h)) % n, mid2 = (suf[i - 1] + (1 << h)) % n;
                    if (c[suf[i]] != c[suf[i - 1]] || c[mid1] != c[mid2]) {
                        ++classes;
                    }
                    temp2[suf[i]] = classes - 1;
                }
                System.arraycopy(temp2, 0, c, 0, n);
            }
            return suf;
        }
    }


    public static class Huffman {
        private static final int R = 256;

        private static class Node implements Comparable<Node> {
            private final char ch;
            private final int freq;
            private final Node left, right;

            Node(char ch, int freq, Node left, Node right) {
                this.ch = ch;
                this.freq = freq;
                this.left = left;
                this.right = right;
            }

            private boolean isLeaf() {
                return (left == null && right == null);
            }

            public int compareTo(Node that) {
                return this.freq - that.freq;
            }
        }

        public static byte[] encode(String s) {
            char[] input = s.toCharArray();
            int[] freq = new int[R];
            for (char anInput : input) freq[anInput]++;

            Node root = buildTrie(freq);

            String[] st = new String[R];
            buildCode(st, root, "");

            writeTrie(root);

            write(input.length);

            for (char anInput : input) {
                String code = st[anInput];
                for (int j = 0; j < code.length(); j++) {
                    if (code.charAt(j) == '0') {
                        writeBit(false);
                    } else if (code.charAt(j) == '1') {
                        writeBit(true);
                    }
                }
            }
            return to(out);
        }

        private static Node buildTrie(int[] freq) {
            MinPQ<Node> pq = new MinPQ<Node>();
            for (char i = 0; i < R; i++)
                if (freq[i] > 0)
                    pq.insert(new Node(i, freq[i], null, null));

            while (pq.size() > 1) {
                Node left = pq.delMin();
                Node right = pq.delMin();
                Node parent = new Node('\0', left.freq + right.freq, left, right);
                pq.insert(parent);
            }
            return pq.delMin();
        }

        private static void writeTrie(Node x) {
            if (x.isLeaf()) {
                writeBit(true);
                writeByte(x.ch);
                return;
            }
            writeBit(false);
            writeTrie(x.left);
            writeTrie(x.right);
        }

        private static void buildCode(String[] st, Node x, String s) {
            if (!x.isLeaf()) {
                buildCode(st, x.left, s + '0');
                buildCode(st, x.right, s + '1');
            } else {
                st[x.ch] = s;
            }
        }

        public static String decode(byte[] b) {
            in = b;
            pos = 0;
            StringBuilder res = new StringBuilder();
            fillBuffer();
            Node root = readTrie();

            int length = readInt();

            for (int i = 0; i < length; i++) {
                Node x = root;
                while (!x.isLeaf()) {
                    boolean bit = readBoolean();
                    if (bit) x = x.right;
                    else x = x.left;
                }
                res.append(x.ch);
            }
            return res.toString();
        }


        private static Node readTrie() {
            boolean isLeaf = readBoolean();
            if (isLeaf) {
                return new Node(readChar(), -1, null, null);
            } else {
                return new Node('\0', -1, readTrie(), readTrie());
            }
        }

        private static byte[] in;
        private static int pos = 0;
        private static int buffer;
        private static int N;

        private static byte[] to(BitSet bs) {
            byte[] bytes = new byte[(bs.length() + 7) / 8];
            for (int i = 0; i < bs.length(); i++) {
                if (bs.get(i)) {
                    bytes[i / 8] |= 1 << (7 - i % 8);
                }
            }
            return bytes;
        }

        private static void fillBuffer() {
            if (pos == in.length) return;
            buffer = in[pos++];
            if (buffer < 0) buffer += 256;
            N = 8;
        }

        public static boolean readBoolean() {
            N--;
            boolean bit = ((buffer >> N) & 1) == 1;
            if (N == 0) fillBuffer();
            return bit;
        }

        public static char readChar() {
            if (N == 8) {
                int x = buffer;
                fillBuffer();
                return (char) (x & 0xff);
            }
            int x = buffer;
            x <<= (8 - N);
            int oldN = N;
            fillBuffer();
            N = oldN;
            x |= (buffer >>> N);
            return (char) (x & 0xff);
        }

        public static int readInt() {
            int x = 0;
            for (int i = 0; i < 4; i++) {
                char c = readChar();
                x <<= 8;
                x |= c;
            }
            return x;
        }

        static BitSet out = new BitSet();
        static int posOut = 0;

        public static void writeBit(boolean bit) {
            out.set(posOut++, bit);
        }

        public static void writeByte(int x) {
            for (int i = 0; i < 8; i++) {
                boolean bit = ((x >>> (8 - i - 1)) & 1) == 1;
                writeBit(bit);
            }
        }

        public static void write(int x) {
            writeByte((x >>> 24) & 0xff);
            writeByte((x >>> 16) & 0xff);
            writeByte((x >>> 8) & 0xff);
            writeByte((x) & 0xff);
        }

    }


    public static class MinPQ<Key> implements Iterable<Key> {
        private Key[] pq;
        private int N;
        private Comparator<Key> comparator;


        public MinPQ(int initCapacity) {
            pq = (Key[]) new Object[initCapacity + 1];
            N = 0;
        }


        public MinPQ() {
            this(1);
        }


        public MinPQ(int initCapacity, Comparator<Key> comparator) {
            this.comparator = comparator;
            pq = (Key[]) new Object[initCapacity + 1];
            N = 0;
        }

        public boolean isEmpty() {
            return N == 0;
        }

        public int size() {
            return N;
        }

        public Key min() {
            if (isEmpty()) throw new NoSuchElementException("Priority queue underflow");
            return pq[1];
        }

        private void resize(int capacity) {
            assert capacity > N;
            Key[] temp = (Key[]) new Object[capacity];
            for (int i = 1; i <= N; i++) temp[i] = pq[i];
            pq = temp;
        }


        public void insert(Key x) {
            if (N == pq.length - 1) resize(2 * pq.length);
            pq[++N] = x;
            swim(N);
            assert isMinHeap();
        }

        public Key delMin() {
            if (isEmpty()) throw new NoSuchElementException("Priority queue underflow");
            exch(1, N);
            Key min = pq[N--];
            sink(1);
            pq[N + 1] = null;         // avoid loitering and help with garbage collection
            if ((N > 0) && (N == (pq.length - 1) / 4)) resize(pq.length / 2);
            assert isMinHeap();
            return min;
        }


        private void swim(int k) {
            while (k > 1 && greater(k / 2, k)) {
                exch(k, k / 2);
                k = k / 2;
            }
        }

        private void sink(int k) {
            while (2 * k <= N) {
                int j = 2 * k;
                if (j < N && greater(j, j + 1)) j++;
                if (!greater(k, j)) break;
                exch(k, j);
                k = j;
            }
        }


        private boolean greater(int i, int j) {
            if (comparator == null) {
                return ((Comparable<Key>) pq[i]).compareTo(pq[j]) > 0;
            } else {
                return comparator.compare(pq[i], pq[j]) > 0;
            }
        }

        private void exch(int i, int j) {
            Key swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
        }

        private boolean isMinHeap() {
            return isMinHeap(1);
        }

        private boolean isMinHeap(int k) {
            if (k > N) return true;
            int left = 2 * k, right = 2 * k + 1;
            if (left <= N && greater(k, left)) return false;
            if (right <= N && greater(k, right)) return false;
            return isMinHeap(left) && isMinHeap(right);
        }


        public Iterator<Key> iterator() {
            return new HeapIterator();
        }

        private class HeapIterator implements Iterator<Key> {
            private MinPQ<Key> copy;

            public HeapIterator() {
                if (comparator == null) copy = new MinPQ<Key>(size());
                else copy = new MinPQ<Key>(size(), comparator);
                for (int i = 1; i <= N; i++)
                    copy.insert(pq[i]);
            }

            public boolean hasNext() {
                return !copy.isEmpty();
            }

            public void remove() {
                throw new UnsupportedOperationException();
            }

            public Key next() {
                if (!hasNext()) throw new NoSuchElementException();
                return copy.delMin();
            }
        }

    }

}

