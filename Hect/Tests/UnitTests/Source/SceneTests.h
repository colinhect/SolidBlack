SUITE(Scene)
{
    class Name :
        public Component<Name>
    {
    public:
        std::string name;
    };

    class Position :
        public Component<Position>
    {
    public:
        Vector3<double> position;
    };

    class Velocity :
        public Component<Velocity>
    {
    public:
        Vector3<double> velocity;
    };

    class MovementSystem :
        public System
    {
    public:
        bool includesEntity(const Entity& entity) const
        {
            return entity.hasComponent<Position>() && entity.hasComponent<Velocity>();
        }

        bool hasEntity(Entity entity)
        {
            auto& es = entities();
            return std::find(es.begin(), es.end(), entity) != es.end();
        }
    };

    class NamingSystem :
        public System
    {
    public:
        bool includesEntity(const Entity& entity) const
        {
            return entity.hasComponent<Name>();
        }

        bool hasEntity(Entity entity)
        {
            auto& es = entities();
            return std::find(es.begin(), es.end(), entity) != es.end();
        }
    };

    TEST(CreateAndDestroy)
    {
        Scene scene;

        Entity a = scene.createEntity();

        CHECK(!a.isNull());
        CHECK(!a.isActivated());

        a.destroy();
        
        CHECK(!a.isNull());
        CHECK(!a.isActivated());

        scene.refresh();

        CHECK(a.isNull());
    }

    TEST(AddComponent)
    {
        Scene scene;

        Entity a = scene.createEntity();

        CHECK(!a.hasComponent<Name>());

        a.addComponent<Name>();

        CHECK(a.hasComponent<Name>());

        Name& name = a.component<Name>();
        name.name = "Testing";

        CHECK_EQUAL("Testing", a.component<Name>().name);
    }

    TEST(ActivationAndDestruction)
    {
        Scene scene;

        Entity a = scene.createEntity();

        CHECK(!a.isActivated());

        a.addComponent<Name>();

        CHECK(!a.isActivated());
        CHECK(a.hasComponent<Name>());

        a.activate();

        CHECK(a.isActivated());

        scene.refresh();

        CHECK(a.isActivated());

        a.destroy();
        scene.refresh();

        CHECK(!a.isActivated());
        CHECK(a.isNull());
    }

    TEST(PoolResize)
    {
        Scene scene;

        // Add a lot of entities
        std::vector<Entity> entities;
        for (int i = 0 ; i < 255; ++i)
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
        
        Scene scene;

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

    TEST(CloneSimpleEntity)
    {
        Scene scene;

        Entity a = scene.createEntity();
        Entity b = a.clone();
        
        CHECK(a != b);
    }

    TEST(CloneEntityWithComponent)
    {
        Scene scene;

        Entity a = scene.createEntity();
        a.addComponent<Name>().name = "Testing";

        CHECK_EQUAL("Testing", a.component<Name>().name);

        Entity b = a.clone();
        
        CHECK(b.hasComponent<Name>());
        CHECK(&a.component<Name>() != &b.component<Name>());
        CHECK_EQUAL("Testing", b.component<Name>().name);
    }

    TEST(CloneActivatedEntity)
    {
        Scene scene;

        Entity a = scene.createEntity();
        a.activate();

        CHECK(a.isActivated());

        Entity b = a.clone();

        CHECK(!b.isActivated());
    }
}
