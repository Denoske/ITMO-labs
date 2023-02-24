package Lab2.beans;

import javax.faces.context.FacesContext;
import javax.persistence.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class ExecutionBean {
    private Data newData;
    private List<DataBean> results;
    ArrayList<DataBean> data = new ArrayList<>();
    EntityManagerFactory emf = Persistence.createEntityManagerFactory("default");


    public ExecutionBean()
    {
        newData = new Data();
        results = new ArrayList<>();

        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            em.persist(newData);
            newData = new Data();
            Query query = em.createQuery("select c from Data c");
            results = query.getResultList();
            tx.commit();

        }catch (RuntimeException c){
            if (tx.isActive()){
                tx.rollback();
            }
            throw c;
        }
    }

    public ArrayList<DataBean> getData() {
        return data;
    }

    public void setData(ArrayList<DataBean> data) {
        this.data = data;
    }

    public void addData(double x, double y, int r)
    {

    }

    public void submit()
    {
        FacesContext context = FacesContext.getCurrentInstance();
        DataBean data = (DataBean) context.getApplication().createValueBinding("#{data}").getValue(context);
        addData(new DataBean(data));
    }

    public void reset(){

        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
    try{
        tx.begin();
        Query query = em.createQuery("DELETE FROM Data c");
        query.executeUpdate();
        results.clear();
        tx.commit();
    }catch (RuntimeException c) {
        if (tx.isActive()){
            tx.rollback();
        }
        throw c;
    }
    data.clear();

    }

    public void addData(DataBean data)
    {
        data.setInside(checkIfInside(data.getX(), data.getY(), data.getR()));
        this.data.add(data);

        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        tx.begin();

        Data data1 = new Data(data.getX(), data.getY(), data.getR(), data.isInside());

        em.persist(data1);
        tx.commit();
        em.close();
    }

    private boolean checkIfInside(double x, double y, int r)
    {
        if (x > 0)
        {
            if (y > 0)
                return y<=r && x<=r;
            else
                return y*y<=r*r-x*x;
        }
        else
        {
            if (y > 0)
                return y<=x+r;
            else
                return false;
        }
    }

    public String circles()
    {
        return Arrays.toString(data.toArray());
    }
}