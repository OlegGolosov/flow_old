//
// Created by Lukas Kreis on 30.01.18.
//


#include <gtest/gtest.h>
#include "Correlation/Correlation.h"

TEST(CorrelationTest, IntegratedCorrelation) {
  Qn::DataContainer<Qn::QVector> container_a;
//  container_a.AddAxes({{"a1", 10, 0, 10}, {"a2", 10, 0, 10}});
  for (auto &bin : container_a) {
    Qn::QVec qvec(1.0,1.0);
    std::array<Qn::QVec, 4> vecarray = {{qvec,qvec,qvec,qvec}};
    bin = Qn::QVector(Qn::QVector::Normalization::NOCALIB, 1, 1, vecarray);
  }
  Qn::DataContainer<Qn::QVector> container_b(container_a);

  std::vector<Qn::Axis> axes = {{"eva1",10,0,10}};

  auto lambda = [](std::vector<Qn::QVector> &a) {return a[0].x(1) + a[1].x(1);};

  Qn::Correlation correlation({container_a,container_b}, axes, lambda);
  for (int i = 0; i<10; ++i) {
    correlation.Fill({container_a,container_b},{i});
  }
  for (auto bin : correlation.GetCorrelation()) {
    EXPECT_EQ(2, bin.Mean());
  }
  EXPECT_EQ(10, correlation.GetCorrelation().size());
}

TEST(CorrelationTest, DifferentialCorrelation) {
  Qn::DataContainer<Qn::QVector> container_a;
  container_a.AddAxes({{"a1", 10, 0, 10}, {"a2", 10, 0, 10}});
  for (auto &bin : container_a) {
    Qn::QVec qvec(1.0,1.0);
    std::array<Qn::QVec, 4> vecarray = {{qvec,qvec,qvec,qvec}};
    bin = Qn::QVector(Qn::QVector::Normalization::NOCALIB, 1, 1, vecarray);
  }
  Qn::DataContainer<Qn::QVector> container_b(container_a);

  std::vector<Qn::Axis> axes = {{"eva1",10,0,10}};

  auto lambda = [](std::vector<Qn::QVector> &a) {return a[0].x(1) + a[1].x(1);};

  Qn::Correlation correlation({container_a,container_b}, axes, lambda);
  for (int i = 0; i<10; ++i) {
    correlation.Fill({container_a,container_b},{i});
  }
  for (auto bin : correlation.GetCorrelation()) {
    EXPECT_EQ(2, bin.Mean());
  }
  EXPECT_EQ(100000, correlation.GetCorrelation().size());
}

TEST(CorrelationTest, DiffPlusIntCorrelation) {
  Qn::DataContainer<Qn::QVector> container_a;
  container_a.AddAxes({{"a1", 10, 0, 10}, {"a2", 10, 0, 10}});
  for (auto &bin : container_a) {
    Qn::QVec qvec(1.0,1.0);
    std::array<Qn::QVec, 4> vecarray = {{qvec,qvec,qvec,qvec}};
    bin = Qn::QVector(Qn::QVector::Normalization::NOCALIB, 1, 1, vecarray);
  }
  Qn::DataContainer<Qn::QVector> container_b;
  for (auto &bin : container_b) {
    Qn::QVec qvec(1.0,1.0);
    std::array<Qn::QVec, 4> vecarray = {{qvec,qvec,qvec,qvec}};
    bin = Qn::QVector(Qn::QVector::Normalization::NOCALIB, 1, 1, vecarray);
  }
  std::vector<Qn::Axis> axes = {{"eva1",10,0,10}};

  auto lambda = [](std::vector<Qn::QVector> &a) {return a[0].x(1) + a[1].x(1);};

  Qn::Correlation correlation({container_a,container_b}, axes, lambda);
  for (int i = 0; i<10; ++i) {
    correlation.Fill({container_a,container_b},{i});
  }
  for (auto bin : correlation.GetCorrelation()) {
    EXPECT_EQ(2, bin.Mean());
  }
  EXPECT_EQ(1000, correlation.GetCorrelation().size());
}