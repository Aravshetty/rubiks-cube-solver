#include "NibbleArray.h"

using namespace std;

NibbleArray::NibbleArray(const size_t size,const uint8_t val):
 size(size), arr(size / 2 + 1, (val & 0x0F) | ((val & 0x0F) << 4)) 
{

}
uint8_t NibbleArray:: get(const size_t pos)const{
  size_t i=pos/2;
  assert(pos<this->size);
  uint8_t val = this->arr.at(i);

  if(pos%2!=0){
    return val& 0x0F;
  }else{
    return val>>4;
  }
}
void NibbleArray::set(const size_t pos, const uint8_t val){
  size_t i=pos/2;
  assert(pos<this->size);
  uint8_t currval=this->arr.at(i);
    if (pos % 2) {
        this->arr.at(i) = (currval & 0xF0) | (val & 0x0F);

    } else {
        this->arr.at(i) = (currval & 0x0F) | ((val & 0x0F) << 4);
    }
}

uint8_t *NibbleArray::data(){
    return this->arr.data();
}
const uint8_t *NibbleArray::data() const{
  return this->arr.data();
}
size_t NibbleArray::storageSize() const {
    return this->arr.size();
}
void NibbleArray::inflate(vector<uint8_t>& dest) const{
        dest.clear();
        dest.reserve(this->size);
        for(size_t i=0;i<this->size;i++){
            dest.push_back(this->get(i));
        }
}

void NibbleArray::reset(const uint8_t val) {
    uint8_t packed = (val & 0x0F) | ((val & 0x0F) << 4);
    fill(this->arr.begin(), this->arr.end(), packed);
}
