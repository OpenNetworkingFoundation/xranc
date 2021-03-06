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

#ifndef _ABSTRACT_BUNDLE_COMPONENT_H_
#define _ABSTRACT_BUNDLE_COMPONENT_H_

#define BUNDLE_VERSION "1.0.0"

#include <iostream>
#include <map>

class AbstractBundleComponent {
    public:
        AbstractBundleComponent() = default;
        ~AbstractBundleComponent() = default;
        virtual void notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message) = 0;
        virtual void registerBundle() = 0;
        virtual void unregisterBundle() = 0;

        virtual void init() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void deinit() = 0;

    protected:

    private:

};

#endif /* _ABSTRACT_BUNDLE_COMPONENT_H_ */