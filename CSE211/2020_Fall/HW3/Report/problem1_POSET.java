import java.util.ListIterator;
import java.util.Random;
import java.util.Vector;

/**
 * Relation class to determine properties of the relation
 * @author Abdullah Çelik
 */
public class problem1_POSET
{
    /** Relation's domain */
    private Vector<String> set;
    /** Relation involving pairs */
    private Vector<Pair> relation;

    /**
     * Builds relation class.
     */
    public problem1_POSET()
    {
        set = new Vector<>(); // Allocate memory for set
        relation = new Vector<>(); // Allocate memory for relation
    }

    /**
     * Adds the given item to the set. If the item already exists, it doesn't add.
     * @param item given item to add
     */
    public void addElement(String item)
    {
        if(set.contains(item))  // If the set contains item
            return; // return from method
        set.add(item);  // Else add item to the set
    }

    /**
     * Adds given pair to the relation. If the set doesn't contain given pair elements, it doesn't add.
     * @param first first element of the given pair
     * @param last last element of the given pair
     * @return true, if given relation is valid. Otherwise, false
     */
    public boolean addRelation(String first, String last)
    {
        if(!set.contains(first) || !set.contains(last)) // If the set doesn't contain given elements
            return false; // return from method

        Pair p = new Pair(first,last); // Else, create a pair with given elements

        if(relation.contains(p)) // If the relation contains created pair
            return true; // return from method

        relation.add(p); // Otherwise, add pair to the relation
        return true;
    }

    /**
     * Makes the relation reflexive if the relation is not reflexive.
     */
    public void makeReflexive()
    {
        Pair p;

        for(String s : set) // Checks all the set elements
            if(!relation.contains((p = new Pair(s,s))))  // If the relation does not contain (s,s)
                relation.add(p); // Add (s,s) to relation
    }

    /**
     * Antisymmetric or not.
     * @return true if the relation is antisymmetric
     */
    public boolean isAntiSymmetric()
    {
        for(Pair p : relation)
            if(!p.isSameElement() && relation.contains(p.getSymmetric()))
                return false;
        return true;
    }

    /**
     * Makes the relation anti-symmetric if the relation is not anti-symmetric.
     * If relation contains (a,b) and (b,a), then (b,a) will be deleted.
     */
    public void makeAntiSymmetric()
    {
        Vector<Pair> symmetric = new Vector<>();
        Random rand = new Random();

        for(Pair p : relation)
            if(!p.isSameElement() && relation.contains(p.getSymmetric()))
                symmetric.add(p);

        for(Pair p : symmetric)
        {
            if(rand.nextInt() % 2 == 0)
                relation.remove(p);
            else
                relation.remove(p.getSymmetric());
        }
    }

    /**
     * Transitive or not.
     * @return true if the relation is transitive
     */
    public boolean isTransitive()
    {
        for(Pair p : relation)
            for(Pair q : relation)
                if(!p.isSameElement() && !p.equals(q) && p.getLast().equals(q.getFirst()) && !relation.contains(new Pair(p.getFirst(),q.getLast())))
                    return false;
        return true;
    }

    /**
     * Makes the relation transitive if the relation is not transitive.
     * If relation contains (a,b), (b,c) but doesn't contain (a,c), then (a,c) will be inserted.
     */
    public void makeTransitive()
    {
        Pair p, q, t;

        for(int i=0 ; i < relation.size() ; ++i) // Examines the pairs of the entire relation for each pair of relation
            for(int j=0 ; j < relation.size() ; ++j)
            {
                p = relation.get(i);
                q = relation.get(j);
                // If pair is not reflexive and pair p is (a,b), pair q is (b,c). Checks the relation contains (a,c)
                if(!p.isSameElement() && !p.equals(q) && p.getLast().equals(q.getFirst()) && !relation.contains((t = new Pair(p.getFirst(),q.getLast()))))
                    relation.add(t);
            }
    }

    /**
     * Makes relation to hasse diagram. Reflexive, transitive pairs will be removed.
     * @return hasse diagram relation
     */
    private Vector<Pair> makeHasseDiagram()
    {
        Vector<Pair> rel = new Vector<>(relation);
        Vector<Pair> rem = new Vector<>(relation.size());
        Pair t;

        rel.removeIf(Pair::isSameElement); // If the relation contains reflexive elements, removes them

        for(Pair p : rel)   // If the relation contains transitive elements, add them to remove container
            for(Pair q : rel)
                if(!p.isSameElement() && !p.equals(q) && p.getLast().equals(q.getFirst()) && relation.contains((t = new Pair(p.getFirst(),q.getLast()))))
                    rem.add(t);

        rel.removeAll(rem); // Remove transitive pair
        return rel;
    }

    /**
     * Returns string representation of the relation.
     * @return string representation of the relation
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        for(Pair pair : relation)
            sb.append(pair);

        return sb.toString();
    }

    /**
     * Returns string representation of the hasse diagram.
     * @return string representation of the hasse diagram
     */
    public String toHasseDiagram()
    {
        StringBuilder sb = new StringBuilder("POSET: ");

        while(!isAntiSymmetric() || !isTransitive())
        {
            makeAntiSymmetric();
            makeTransitive();
        }
        makeReflexive();

        for(Pair pair : relation)   // Adds each element of poset
            sb.append(pair).append(", ");
        sb.delete(sb.length()-2,sb.length()).append('\n');

        Vector<Pair> hasse = makeHasseDiagram();

        if(hasse.size() == 0)
            return sb.append("Empty set!\n").toString();

        for(Pair pair : hasse)  // Adds hasse diagram edges
            sb.append(pair.getFirst()).append(',').append(pair.getLast()).append('\n');

        return sb.toString();
    }

    /**
     * Pair for the relation class
     */
    public static class Pair
    {
        /** First element of pair */
        private String first;
        /** Second element of pair */
        private String last;

        /**
         * Construct pair class with given elements.
         * @param first given first element
         * @param last given last element
         */
        public Pair(String first, String last)
        {
            this.first = first;
            this.last = last;
        }

        /**
         * Getter for first element of pair.
         * @return first element
         */
        public String getFirst() { return first; }

        /**
         * Getter for last element of pair.
         * @return last element
         */
        public String getLast() { return last; }

        /**
         * Returns symmetric version of pair. For example, pair is (a,b), returns (b,a).
         * @return symmetric version of pair
         */
        public Pair getSymmetric() { return new Pair(getLast(),getFirst()); }

        /**
         * Checks whether first element and last element are equal.
         * @return true, if first and last element are equal. Otherwise, false
         */
        public boolean isSameElement() { return getFirst().equals(getLast()); }

        /**
         * Checks whether given other object is equal this object.
         * @param o other object
         * @return true, if given other object and this object are equal
         */
        @Override
        public boolean equals(Object o)
        {
            if(o == null)
                return false;
            if(!(o instanceof  Pair))
                return false;

            return ((Pair)o).getFirst().equals(getFirst()) && ((Pair)o).getLast().equals(getLast());
        }

        /**
         * Returns string representation of the pair class.
         * @return string representation of the pair class
         */
        @Override
        public String toString() { return "(" + getFirst() + ", " + getLast() + ")"; }
    }
}