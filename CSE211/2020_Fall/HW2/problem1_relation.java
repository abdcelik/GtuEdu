import java.util.Vector;

/**
 * Relation class to determine properties of the relation
 * @author Abdullah Çelik
 */
public class problem1_relation
{
    /** Relation's domain */
    private Vector<String> set;
    /** Relation involving pairs */
    private Vector<Pair> relation;

    /**
     * Builds relation class.
     */
    public problem1_relation()
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
     * Checks whether the relation is reflexive or not.
     * @return string representation of the result
     */
    public String isReflexive()
    {
        StringBuilder sb = new StringBuilder("Reflexive: Yes, "); // Creates a string builder like the relation is reflexive
        Pair p;

        for(String s : set) // Checks all the set elements
            if(relation.contains((p = new Pair(s,s))))  // If the relation contains s,s
                sb.append(p).append(" "); // Appends that pair
            else
                return "Reflexive: No, " + p + " is not found.\n"; // Otherwise, the relation isn't reflexive. Builds string as relation is not reflexive

        return sb.append("are found.\n").toString();
    }

    /**
     * Checks whether the relation is symmetric or not.
     * @return string representation of the result
     */
    public String isSymmetric()
    {
        StringBuilder sb = new StringBuilder("Symmetric: Yes, "); // Create a string builder like the relation is symmetric
        Pair q;
        boolean flag = true; // only for one reason why is symmetric

        for(Pair p : relation) // Checks all pairs of relation
            if(!p.isSameElement()) // If pair is not reflexive
            {
                if(relation.contains((q = p.getSymmetric()))) // If the relation contains pair's symmetric version
                {
                    if(flag)
                    {
                        sb.append(q).append(" is found whereas ").append(p).append(" is found. "); // Appends that pair
                        flag = false;
                    }
                }
                else
                    return "Symmetric: No, " + q + " is not found whereas " + p + " is found.\n"; // Otherwise, the relation isn't symmetric. Builds string as the relation is not symmetric
            }

        return sb.append("Symmetries of all elements are found.\n").toString();
    }

    /**
     * Checks whether the relation is antisymmetric or not.
     * @return string representation of the result
     */
    public String isAntisymmetric()
    {
        StringBuilder sb = new StringBuilder("Antisymmetric: Yes, "); // Create a string builder like the relation is antisymmetric
        Pair q;
        boolean flag = true; // only for one reason why is antisymmetric

        for(Pair p : relation) // Checks all pairs of relation
            if(!p.isSameElement()) // If pair is not reflexive
            {
                if(relation.contains((q = p.getSymmetric()))) // If the relation contains pair's symmetric version
                    return "Antisymmetric: No, " + p + " and " + q + " are found.\n"; // The relation isn't antisymmetric. Builds string as the relation is not antisymmetric
                else
                {
                    if(flag)
                    {
                        sb.append(p).append(" is found but ").append(q).append(" is not found. "); // Otherwise, appends that pair
                        flag = false;
                    }
                }
            }

        return sb.append("There is no element that breaks the antisymmetry.\n").toString();
    }

    /**
     * Checks whether the relation is transitive or not.
     * @return string representation of the result
     */
    public String isTransitive()
    {
        StringBuilder sb = new StringBuilder("Transitive: Yes, "); // Create a string builder like the relation is transitive
        Pair t;
        boolean flag = true; // only for one reason why is transitive

        for(Pair p : relation) // Examines the pairs of the entire relation for each pair of relation
            for(Pair q : relation)
                if(!p.isSameElement() && !p.equals(q) && p.getLast().equals(q.getFirst())) // If pair is not reflexive and pair p is (a,b), pair q is (b,c)
                {
                    if(relation.contains((t = new Pair(p.getFirst(),q.getLast())))) // Checks the relation contains (b,c)
                    {
                        if(flag)
                        {
                            sb.append(t).append(" is found whereas ").append(p).append(" and ").append(q).append(" are found. "); // Appends that pairs
                            flag = false;
                        }
                    }
                    else
                        return "Transitive: No, " + t + " is not found whereas " + p + " and " + q + " are found.\n"; // Otherwise, the relation isn't transitive. Builds string as the relation is not transitive
                }

        return sb.append("There is no element that breaks the transitivity\n").toString();
    }

    /**
     * Returns string representation of the relation.
     * @return string representation of the relation
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        for(Pair pair : relation) sb.append(pair);
        return sb.append("\n").append(isReflexive()).append(isSymmetric()).append(isAntisymmetric()).append(isTransitive()).toString();
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
        public String toString() { return "(" + getFirst() + "," + getLast() + ")"; }
    }
}
