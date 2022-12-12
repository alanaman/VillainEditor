#include "logging.hpp"
#include "actor.hpp"
#include "model.hpp"

namespace villain {


class Gunner : public Actor
{
private:
 std::shared_ptr<Model> model;

public:
 Gunner(std::string name, std::shared_ptr<Model> model);
 virtual void beginPlay() override;
 virtual void updateOnFrame() override;

 virtual std::shared_ptr<Model> getModel() override;

};
}