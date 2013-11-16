class Name :
    public EntityComponent<Name>
{
public:
    std::string name;
};

class Position :
    public EntityComponent<Position>
{
public:
    Vector3<double> position;
};

class Velocity :
    public EntityComponent<Velocity>
{
public:
    Vector3<double> velocity;
};

class Animal :
    public EntityComponent<Animal>
{
public:
    virtual bool isDog() const = 0;
    virtual bool isCat() const = 0;
};

class Dog :
    public Animal
{
public:
    bool isDog() const
    {
        return true;
    }
    bool isCat() const
    {
        return false;
    }
};

class Cat :
    public Animal
{
public:
    bool isDog() const
    {
        return false;
    }
    bool isCat() const
    {
        return true;
    }
};

class MovementSystem :
    public EntitySystem
{
public:
    MovementSystem()
    {
        requireComponent<Position>();
        requireComponent<Velocity>();
    }

    bool hasEntity(Entity entity)
    {
        auto& es = entities();
        return std::find(es.begin(), es.end(), entity) != es.end();
    }
};

class NamingSystem :
    public EntitySystem
{
public:
    NamingSystem()
    {
        requireComponent<Name>();
    }

    bool hasEntity(Entity entity)
    {
        auto& es = entities();
        return std::find(es.begin(), es.end(), entity) != es.end();
    }
};

struct NotEntity
{
    NotEntity(uint32_t id) :
        id(id)
    {
    }

    uint32_t id;
};

SUITE(Entity)
{
    TEST(CreateAndDestroy)
    {
        Scene scene(16);

        Entity a = scene.createEntity();
        CHECK(!a.isNull());

        a.destroy();
        CHECK(!a.isNull());
        scene.refresh();
        CHECK(a.isNull());
    }

    TEST(Components)
    {
        Scene scene(16);
        Entity a = scene.createEntity();

        CHECK(!a.hasComponent<Name>());
        a.addComponent<Name>();
        CHECK(a.hasComponent<Name>());

        CHECK_EQUAL("", a.component<Name>().name);
    }

    TEST(PolymorphicComponents)
    {
        Scene scene(16);

        Entity a = scene.createEntity();
        a.addComponent<Dog>();
        CHECK(a.hasComponent<Animal>());
        CHECK(a.component<Animal>().isDog());
        CHECK(!a.component<Animal>().isCat());

        Entity b = scene.createEntity();
        b.addComponent<Cat>();
        CHECK(b.hasComponent<Animal>());
        CHECK(!b.component<Animal>().isDog());
        CHECK(b.component<Animal>().isCat());
    }

    TEST(ActivationAndDestruction)
    {
        Scene scene(16);
        Entity a = scene.createEntity();
        CHECK(!a.isActivated());
        a.addComponent<Name>();
        CHECK(!a.isActivated());

        a.activate();
        scene.refresh();
        CHECK(a.isActivated());

        a.destroy();
        scene.refresh();
        CHECK(!a.isActivated());
        CHECK(a.isNull());
    }

    TEST(PoolResize)
    {
        Scene scene(4);

        std::vector<Entity> entities;
        for (int i = 0 ; i < 8; ++i)
        {
            Entity entity = scene.createEntity();
            entity.addComponent<Name>();
            entities.push_back(entity);
        }

        for (Entity& entity : entities)
        {
            CHECK(!entity.isNull());
            CHECK(entity.hasComponent<Name>());
            CHECK_EQUAL("", entity.component<Name>().name);
        }
    }

    TEST(Systems)
    {
        MovementSystem movementSystem;
        NamingSystem namingSystem;

        Scene scene(16);

        scene.addSystem(movementSystem);
        scene.addSystem(namingSystem);

        Entity frank = scene.createEntity();
        frank.addComponent<Name>().name = "Frank";
        frank.addComponent<Velocity>();
        frank.activate();

        Entity joe = scene.createEntity();
        joe.addComponent<Name>().name = "Joe";
        joe.addComponent<Velocity>();
        joe.addComponent<Position>();
        joe.activate();

        Entity namelessHerold =  scene.createEntity();
        namelessHerold.addComponent<Velocity>();
        namelessHerold.addComponent<Position>();
        namelessHerold.activate();

        scene.refresh();

        CHECK(!movementSystem.hasEntity(frank));
        CHECK(movementSystem.hasEntity(joe));
        CHECK(movementSystem.hasEntity(namelessHerold));

        CHECK(namingSystem.hasEntity(frank));
        CHECK(namingSystem.hasEntity(joe));
        CHECK(!namingSystem.hasEntity(namelessHerold));

        frank.destroy();
        scene.refresh();

        CHECK(!movementSystem.hasEntity(frank));
        CHECK(movementSystem.hasEntity(joe));
        CHECK(movementSystem.hasEntity(namelessHerold));

        CHECK(!namingSystem.hasEntity(frank));
        CHECK(namingSystem.hasEntity(joe));
        CHECK(!namingSystem.hasEntity(namelessHerold));

        joe.destroy();
        scene.refresh();

        CHECK(!movementSystem.hasEntity(frank));
        CHECK(!movementSystem.hasEntity(joe));
        CHECK(movementSystem.hasEntity(namelessHerold));

        CHECK(!namingSystem.hasEntity(frank));
        CHECK(!namingSystem.hasEntity(joe));
        CHECK(!namingSystem.hasEntity(namelessHerold));
    }
}
