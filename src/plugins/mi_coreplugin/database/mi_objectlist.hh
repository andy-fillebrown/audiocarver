bool isEmpty() const
{
    return d_ptr->objects.isEmpty();
}

int count() const
{
    return d_ptr->objects.count();
}

const QList<T*> &asQList() const
{
    return reinterpret_cast<const QList<T*>&>(d_ptr->objects);
}

T *const &at(int i) const
{
    return asQList().at(i);
}

T *&operator[](int i)
{
    return asQList()[i];
}

const T *&operator[](int i) const
{
    return at(i);
}
void insert(int i, T* object)
{
    d_ptr->beginInsert(i, i);
    d_ptr->insert(i, object);
    d_ptr->endInsert(i, i);
}

void insert(int i, const QList<T*> &objects)
{
    const int end = i + objects.count() - 1;
    d_ptr->beginInsert(i, end);
    int j = i - 1;
    foreach (T* object, objects)
        d_ptr->insert(++j, object);
    d_ptr->endInsert(i, end);
}

void append(T* object)
{
    insert(count(), object);
}

void append(const QList<T*> &objects)
{
    insert(count(), objects);
}

void move(int i, int destination)
{
    d_ptr->beginMove(i, i, destination);
    d_ptr->objects.move(i, destination);
    d_ptr->endMove(i, i, destination);
}

void move(int i, int count, int destination)
{
    const int end = i + count - 1;
    d_ptr->beginMove(i, end, destination);
    QList<T*> taken;
    taken.reserve(count);
    for (int j = i;  j <= end;  ++j)
        taken.append(d_ptr->objects.takeAt(i));
    int k = destination - 1;
    foreach (QObject *object, taken)
        d_ptr->objects.insert(++k, object);
    d_ptr->endMove(i, end, destination);
}

void removeAt(int i)
{
    d_ptr->beginRemove(i, i);
    d_ptr->objects.removeAt(i);
    d_ptr->endRemove(i, i);
}

void removeAt(int i, int count)
{
    const int end = i + count - 1;
    d_ptr->beginRemove(i, end);
    for (int j = i;  j <= end;  ++j)
        d_ptr->objects.removeAt(j);
    d_ptr->endRemove(i, end);
}

void removeOne(const T* object)
{
    removeAt(d_ptr->objects.indexOf(object));
}
