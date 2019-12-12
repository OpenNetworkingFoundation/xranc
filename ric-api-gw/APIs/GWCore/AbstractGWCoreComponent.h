/*
 * Copyright 2019-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ABSTRACT_GWCORE_COMPONENT_H_
#define _ABSTRACT_GWCORE_COMPONENT_H_

#define GWCORE_VERSION "1.0.0"
#define GWCORE_NAME "GWCore"

#include <iostream>
#include <map>
#include <string>

#include "../Bundles/AbstractBundleComponent.h"

class AbstractGWCoreComponent {
    public:
        AbstractGWCoreComponent() = default;
        ~AbstractGWCoreComponent() = default;
        virtual void notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message) = 0;
        virtual void registerBundle(std::string key, AbstractBundleComponent* bundleComponent) = 0;
        virtual void unregisterBundle(std::string key) = 0;
        std::map<std::string, AbstractBundleComponent*> getBundles() {
            return this->bundles;
        }

        void setBundles(std::map<std::string, AbstractBundleComponent*> bundles) {
            for (std::map<std::string, AbstractBundleComponent*>::iterator it = bundles.begin(); it != bundles.end(); it = ++it) {
                addBundle(it->first, it->second);
            }
        }

        void addBundle(std::string key, AbstractBundleComponent* bundleComponent) {
            bundles.insert({key, bundleComponent});
        }

        AbstractBundleComponent* getBundle(std::string key) {
            return bundles.at(key);
        }

        void removeBundle(std::string key) {
            bundles.erase(key);
        }

    protected:
        std::map<std::string, AbstractBundleComponent*> bundles;
    private:

};

#endif /* _ABSTRACT_GWCORE_COMPONENT_H_ */